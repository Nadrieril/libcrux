use crate::{
    arithmetic::{
        decompose_vector, make_hint, power2round_vector, use_hint, vector_infinity_norm_exceeds,
    },
    constants::*,
    encoding,
    hash_functions::H,
    matrix::{
        add_vectors, compute_A_times_mask, compute_As1_plus_s2, compute_w_approx, expand_to_A,
        subtract_vectors, vector_times_ring_element,
    },
    ntt::ntt_simd,
    polynomial::PolynomialRingElement,
    sample::{sample_challenge_ring_element, sample_error_vector, sample_mask_vector},
    simd::traits::Operations,
    utils::into_padded_array,
};

pub(crate) struct Signature<
    const COMMITMENT_HASH_SIZE: usize,
    const COLUMNS_IN_A: usize,
    const ROWS_IN_A: usize,
> {
    pub commitment_hash: [u8; COMMITMENT_HASH_SIZE],
    pub signer_response: [PolynomialRingElement; COLUMNS_IN_A],
    pub hint: [[i32; COEFFICIENTS_IN_RING_ELEMENT]; ROWS_IN_A],
}

#[allow(non_snake_case)]
pub(crate) fn generate_key_pair<
    SIMDUnit: Operations,
    const ROWS_IN_A: usize,
    const COLUMNS_IN_A: usize,
    const ETA: usize,
    const ERROR_RING_ELEMENT_SIZE: usize,
    const SIGNING_KEY_SIZE: usize,
    const VERIFICATION_KEY_SIZE: usize,
>(
    randomness: [u8; KEY_GENERATION_RANDOMNESS_SIZE],
) -> ([u8; SIGNING_KEY_SIZE], [u8; VERIFICATION_KEY_SIZE]) {
    // 128 = SEED_FOR_A_SIZE + SEED_FOR_ERROR_VECTORS_SIZE + SEED_FOR_SIGNING_SIZE
    let seed_expanded = H::one_shot::<128>(&randomness);

    let (seed_for_A, seed_expanded) = seed_expanded.split_at(SEED_FOR_A_SIZE);
    let (seed_for_error_vectors, seed_for_signing) =
        seed_expanded.split_at(SEED_FOR_ERROR_VECTORS_SIZE);

    let mut domain_separator: u16 = 0;

    let A_as_ntt = expand_to_A::<SIMDUnit, ROWS_IN_A, COLUMNS_IN_A>(into_padded_array(seed_for_A));

    let s1 = sample_error_vector::<SIMDUnit, COLUMNS_IN_A, ETA>(
        into_padded_array(seed_for_error_vectors),
        &mut domain_separator,
    );
    let s2 = sample_error_vector::<SIMDUnit, ROWS_IN_A, ETA>(
        into_padded_array(seed_for_error_vectors),
        &mut domain_separator,
    );

    let t = compute_As1_plus_s2::<SIMDUnit, ROWS_IN_A, COLUMNS_IN_A>(&A_as_ntt, &s1, &s2);

    let (t0, t1) = power2round_vector::<SIMDUnit, ROWS_IN_A>(t);

    let verification_key_serialized = encoding::verification_key::generate_serialized::<
        SIMDUnit,
        ROWS_IN_A,
        VERIFICATION_KEY_SIZE,
    >(seed_for_A, t1);

    let signing_key_serialized = encoding::signing_key::generate_serialized::<
        SIMDUnit,
        ROWS_IN_A,
        COLUMNS_IN_A,
        ETA,
        ERROR_RING_ELEMENT_SIZE,
        SIGNING_KEY_SIZE,
    >(
        seed_for_A,
        seed_for_signing,
        &verification_key_serialized,
        s1,
        s2,
        t0,
    );

    (signing_key_serialized, verification_key_serialized)
}

#[derive(Debug)]
pub enum VerificationError {
    MalformedHintError,
    SignerResponseExceedsBoundError,
    CommitmentHashesDontMatchError,
}

#[allow(non_snake_case)]
pub(crate) fn sign<
    SIMDUnit: Operations,
    const ROWS_IN_A: usize,
    const COLUMNS_IN_A: usize,
    const ETA: usize,
    const ERROR_RING_ELEMENT_SIZE: usize,
    const GAMMA1_EXPONENT: usize,
    const GAMMA2: i32,
    const COMMITMENT_RING_ELEMENT_SIZE: usize,
    const COMMITMENT_VECTOR_SIZE: usize,
    const COMMITMENT_HASH_SIZE: usize,
    const ONES_IN_VERIFIER_CHALLENGE: usize,
    const MAX_ONES_IN_HINT: usize,
    const GAMMA1_RING_ELEMENT_SIZE: usize,
    const SIGNING_KEY_SIZE: usize,
    const SIGNATURE_SIZE: usize,
>(
    signing_key: [u8; SIGNING_KEY_SIZE],
    message: &[u8],
    randomness: [u8; SIGNING_RANDOMNESS_SIZE],
) -> [u8; SIGNATURE_SIZE] {
    let (seed_for_A, seed_for_signing, verification_key_hash, s1_as_ntt, s2_as_ntt, t0_as_ntt) =
        encoding::signing_key::deserialize_then_ntt::<
            ROWS_IN_A,
            COLUMNS_IN_A,
            ETA,
            ERROR_RING_ELEMENT_SIZE,
            SIGNING_KEY_SIZE,
        >(signing_key);

    let A_as_ntt = expand_to_A::<SIMDUnit, ROWS_IN_A, COLUMNS_IN_A>(into_padded_array(&seed_for_A));

    // TODO: Remove the use of to_vec with an incremental SHAKE-256 absorb API.
    let message_representative = {
        let mut hash_input = verification_key_hash.to_vec();
        hash_input.extend_from_slice(message);

        H::one_shot::<MESSAGE_REPRESENTATIVE_SIZE>(&hash_input[..])
    };

    let mask_seed: [u8; MASK_SEED_SIZE] = {
        let mut hash_input = seed_for_signing.to_vec();
        hash_input.extend_from_slice(&randomness);
        hash_input.extend_from_slice(&message_representative);

        H::one_shot::<MASK_SEED_SIZE>(&hash_input[..])
    };

    let mut domain_separator_for_mask: u16 = 0;

    let BETA = (ONES_IN_VERIFIER_CHALLENGE * ETA) as i32;

    let mut attempt = 0;

    // TODO: This style of rejection sampling, with the break and the continues,
    // won't pass through hax; it'll need to be rewritten.
    // See https://github.com/cryspen/libcrux/issues/341
    let (commitment_hash, signer_response, hint) = loop {
        attempt += 1;

        // Depending on the mode, one try has a chance between 1/7 and 1/4
        // of succeeding.  Thus it is safe to say that 576 iterations
        // are enough as (6/7)⁵⁷⁶ < 2⁻¹²⁸[1].
        //
        // [1]: https://github.com/cloudflare/circl/blob/main/sign/dilithium/mode2/internal/dilithium.go#L341
        debug_assert!(attempt < 576);

        let mask = sample_mask_vector::<COLUMNS_IN_A, GAMMA1_EXPONENT>(
            into_padded_array(&mask_seed),
            &mut domain_separator_for_mask,
        );

        let A_times_mask =
            compute_A_times_mask::<SIMDUnit, ROWS_IN_A, COLUMNS_IN_A>(&A_as_ntt, &mask);

        let (w0, commitment) = decompose_vector::<ROWS_IN_A, GAMMA2>(A_times_mask);

        let commitment_hash: [u8; COMMITMENT_HASH_SIZE] = {
            let commitment_serialized = encoding::commitment::serialize_vector::<
                ROWS_IN_A,
                COMMITMENT_RING_ELEMENT_SIZE,
                COMMITMENT_VECTOR_SIZE,
            >(commitment);

            let mut hash_input = message_representative.to_vec();
            hash_input.extend_from_slice(&commitment_serialized);

            H::one_shot::<COMMITMENT_HASH_SIZE>(&hash_input[..])
        };

        let verifier_challenge_as_ntt = ntt_simd(sample_challenge_ring_element::<
            SIMDUnit,
            ONES_IN_VERIFIER_CHALLENGE,
        >(
            commitment_hash[0..VERIFIER_CHALLENGE_SEED_SIZE]
                .try_into()
                .unwrap(),
        ))
        .to_polynomial_ring_element();

        let challenge_times_s1 =
            vector_times_ring_element::<COLUMNS_IN_A>(&s1_as_ntt, &verifier_challenge_as_ntt);
        let challenge_times_s2 =
            vector_times_ring_element::<ROWS_IN_A>(&s2_as_ntt, &verifier_challenge_as_ntt);

        let signer_response = add_vectors::<COLUMNS_IN_A>(&mask, &challenge_times_s1);

        let w0_minus_challenge_times_s2 = subtract_vectors::<ROWS_IN_A>(&w0, &challenge_times_s2);

        if vector_infinity_norm_exceeds::<COLUMNS_IN_A>(
            signer_response,
            (1 << GAMMA1_EXPONENT) - BETA,
        ) {
            continue;
        }
        if vector_infinity_norm_exceeds::<ROWS_IN_A>(w0_minus_challenge_times_s2, GAMMA2 - BETA) {
            continue;
        }

        let challenge_times_t0 =
            vector_times_ring_element::<ROWS_IN_A>(&t0_as_ntt, &verifier_challenge_as_ntt);
        if vector_infinity_norm_exceeds::<ROWS_IN_A>(challenge_times_t0, GAMMA2) {
            continue;
        }

        let w0_minus_c_times_s2_plus_c_times_t0 =
            add_vectors::<ROWS_IN_A>(&w0_minus_challenge_times_s2, &challenge_times_t0);
        let (hint, ones_in_hint) =
            make_hint::<ROWS_IN_A, GAMMA2>(w0_minus_c_times_s2_plus_c_times_t0, commitment);
        if ones_in_hint > MAX_ONES_IN_HINT {
            continue;
        }

        break (commitment_hash, signer_response, hint);
    };

    Signature::<COMMITMENT_HASH_SIZE, COLUMNS_IN_A, ROWS_IN_A> {
        commitment_hash,
        signer_response,
        hint,
    }
    .serialize::<GAMMA1_EXPONENT, GAMMA1_RING_ELEMENT_SIZE, MAX_ONES_IN_HINT, SIGNATURE_SIZE>()
}

#[allow(non_snake_case)]
pub(crate) fn verify<
    SIMDUnit: Operations,
    const ROWS_IN_A: usize,
    const COLUMNS_IN_A: usize,
    const SIGNATURE_SIZE: usize,
    const VERIFICATION_KEY_SIZE: usize,
    const GAMMA1_EXPONENT: usize,
    const GAMMA1_RING_ELEMENT_SIZE: usize,
    const GAMMA2: i32,
    const BETA: i32,
    const COMMITMENT_RING_ELEMENT_SIZE: usize,
    const COMMITMENT_VECTOR_SIZE: usize,
    const COMMITMENT_HASH_SIZE: usize,
    const ONES_IN_VERIFIER_CHALLENGE: usize,
    const MAX_ONES_IN_HINT: usize,
>(
    verification_key_serialized: [u8; VERIFICATION_KEY_SIZE],
    message: &[u8],
    signature_serialized: [u8; SIGNATURE_SIZE],
) -> Result<(), VerificationError> {
    let (seed_for_A, t1) =
        encoding::verification_key::deserialize::<SIMDUnit, ROWS_IN_A, VERIFICATION_KEY_SIZE>(
            verification_key_serialized,
        );

    let signature = Signature::<COMMITMENT_HASH_SIZE, COLUMNS_IN_A, ROWS_IN_A>::deserialize::<
        GAMMA1_EXPONENT,
        GAMMA1_RING_ELEMENT_SIZE,
        MAX_ONES_IN_HINT,
        SIGNATURE_SIZE,
    >(signature_serialized)?;

    // We use if-else branches because early returns will not go through hax.
    if !vector_infinity_norm_exceeds::<COLUMNS_IN_A>(
        signature.signer_response,
        (2 << GAMMA1_EXPONENT) - BETA,
    ) {
        let A_as_ntt =
            expand_to_A::<SIMDUnit, ROWS_IN_A, COLUMNS_IN_A>(into_padded_array(&seed_for_A));

        let verification_key_hash =
            H::one_shot::<BYTES_FOR_VERIFICATION_KEY_HASH>(&verification_key_serialized);
        let message_representative = {
            let mut hash_input = verification_key_hash.to_vec();
            hash_input.extend_from_slice(message);

            H::one_shot::<MESSAGE_REPRESENTATIVE_SIZE>(&hash_input[..])
        };

        let verifier_challenge_as_ntt = ntt_simd(sample_challenge_ring_element::<
            SIMDUnit,
            ONES_IN_VERIFIER_CHALLENGE,
        >(
            signature.commitment_hash[0..VERIFIER_CHALLENGE_SEED_SIZE]
                .try_into()
                .unwrap(),
        ));

        let w_approx = compute_w_approx::<SIMDUnit, ROWS_IN_A, COLUMNS_IN_A>(
            &A_as_ntt,
            signature.signer_response,
            verifier_challenge_as_ntt,
            t1,
        );

        let commitment_hash: [u8; COMMITMENT_HASH_SIZE] = {
            let commitment = use_hint::<ROWS_IN_A, GAMMA2>(signature.hint, w_approx);
            let commitment_serialized = encoding::commitment::serialize_vector::<
                ROWS_IN_A,
                COMMITMENT_RING_ELEMENT_SIZE,
                COMMITMENT_VECTOR_SIZE,
            >(commitment);

            let mut hash_input = message_representative.to_vec();
            hash_input.extend_from_slice(&commitment_serialized);

            H::one_shot::<COMMITMENT_HASH_SIZE>(&hash_input[..])
        };

        if signature.commitment_hash != commitment_hash {
            Err(VerificationError::CommitmentHashesDontMatchError)
        } else {
            Ok(())
        }
    } else {
        Err(VerificationError::SignerResponseExceedsBoundError)
    }
}
