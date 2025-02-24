use crate::{constants::*, types::*, VerificationError};

// ML-DSA-65-specific parameters

const ROWS_IN_A: usize = 6;
const COLUMNS_IN_A: usize = 5;

const ETA: usize = 4;

// To sample a value in the interval [-ETA, ETA], we can sample a value (say 'v')
// in the interval [0, 2 * ETA] and then compute ETA - v. This can be done in
// 4 bits when ETA is 4.
const BITS_PER_ERROR_COEFFICIENT: usize = 4;

const ERROR_RING_ELEMENT_SIZE: usize =
    (BITS_PER_ERROR_COEFFICIENT * COEFFICIENTS_IN_RING_ELEMENT) / 8;

const GAMMA1_EXPONENT: usize = 19;
// To sample a value in the interval [-(GAMMA - 1), GAMMA], we can sample a
// value (say 'v') in the interval [0, (2 * GAMMA) - 1] and then compute
// GAMMA - v. This can be done in 20 bits when GAMMA is 2^{19}.
const BITS_PER_GAMMA1_COEFFICIENT: usize = 20;
const GAMMA1_RING_ELEMENT_SIZE: usize =
    (BITS_PER_GAMMA1_COEFFICIENT * COEFFICIENTS_IN_RING_ELEMENT) / 8;

const MAX_ONES_IN_HINT: usize = 55;

const ONES_IN_VERIFIER_CHALLENGE: usize = 49;

const GAMMA2: i32 = (FIELD_MODULUS - 1) / 32;

const BETA: i32 = (ONES_IN_VERIFIER_CHALLENGE * ETA) as i32;

// Commitment coefficients are in the interval: [0, ((FIELD_MODULUS − 1)/2γ2) − 1]
// ((FIELD_MODULUS − 1)/2γ2) − 1 = 15, which means we need 4 bits to represent a
// coefficient.
const BITS_PER_COMMITMENT_COEFFICIENT: usize = 4;

const COMMITMENT_RING_ELEMENT_SIZE: usize =
    (BITS_PER_COMMITMENT_COEFFICIENT * COEFFICIENTS_IN_RING_ELEMENT) / 8;
const COMMITMENT_VECTOR_SIZE: usize = COMMITMENT_RING_ELEMENT_SIZE * ROWS_IN_A;

const COMMITMENT_HASH_SIZE: usize = 48;

const VERIFICATION_KEY_SIZE: usize = SEED_FOR_A_SIZE
    + (COEFFICIENTS_IN_RING_ELEMENT
        * ROWS_IN_A
        * (FIELD_MODULUS_MINUS_ONE_BIT_LENGTH - BITS_IN_LOWER_PART_OF_T))
        / 8;

const SIGNING_KEY_SIZE: usize = SEED_FOR_A_SIZE
    + SEED_FOR_SIGNING_SIZE
    + BYTES_FOR_VERIFICATION_KEY_HASH
    + (ROWS_IN_A + COLUMNS_IN_A) * ERROR_RING_ELEMENT_SIZE
    + ROWS_IN_A * RING_ELEMENT_OF_T0S_SIZE;

const SIGNATURE_SIZE: usize =
    COMMITMENT_HASH_SIZE + (COLUMNS_IN_A * GAMMA1_RING_ELEMENT_SIZE) + MAX_ONES_IN_HINT + ROWS_IN_A;

pub type MLDSA65SigningKey = MLDSASigningKey<SIGNING_KEY_SIZE>;
pub type MLDSA65VerificationKey = MLDSAVerificationKey<VERIFICATION_KEY_SIZE>;
pub type MLDSA65KeyPair = MLDSAKeyPair<VERIFICATION_KEY_SIZE, SIGNING_KEY_SIZE>;
pub type MLDSA65Signature = MLDSASignature<SIGNATURE_SIZE>;

// TODO: Multiplex more intelligently.
#[cfg(feature = "simd256")]
type SIMDUnit = crate::simd::avx2::AVX2SIMDUnit;
#[cfg(not(feature = "simd256"))]
type SIMDUnit = crate::simd::portable::PortableSIMDUnit;

#[cfg(feature = "simd256")]
type Shake128 = crate::hash_functions::portable::PortableShake128;
#[cfg(not(feature = "simd256"))]
type Shake128 = crate::hash_functions::portable::PortableShake128;

#[cfg(feature = "simd256")]
type Shake256 = crate::hash_functions::portable::PortableShake256;
#[cfg(not(feature = "simd256"))]
type Shake256 = crate::hash_functions::portable::PortableShake256;

/// Generate an ML-DSA-65 Key Pair
pub fn generate_key_pair(randomness: [u8; KEY_GENERATION_RANDOMNESS_SIZE]) -> MLDSA65KeyPair {
    let (signing_key, verification_key) = crate::ml_dsa_generic::generate_key_pair::<
        SIMDUnit,
        Shake128,
        Shake256,
        ROWS_IN_A,
        COLUMNS_IN_A,
        ETA,
        ERROR_RING_ELEMENT_SIZE,
        SIGNING_KEY_SIZE,
        VERIFICATION_KEY_SIZE,
    >(randomness);

    MLDSA65KeyPair {
        signing_key: MLDSASigningKey(signing_key),
        verification_key: MLDSAVerificationKey(verification_key),
    }
}

/// Generate an ML-DSA-65 Signature
pub fn sign(
    signing_key: &MLDSA65SigningKey,
    message: &[u8],
    randomness: [u8; SIGNING_RANDOMNESS_SIZE],
) -> MLDSA65Signature {
    crate::ml_dsa_generic::sign::<
        SIMDUnit,
        Shake128,
        Shake256,
        ROWS_IN_A,
        COLUMNS_IN_A,
        ETA,
        ERROR_RING_ELEMENT_SIZE,
        GAMMA1_EXPONENT,
        GAMMA2,
        COMMITMENT_RING_ELEMENT_SIZE,
        COMMITMENT_VECTOR_SIZE,
        COMMITMENT_HASH_SIZE,
        ONES_IN_VERIFIER_CHALLENGE,
        MAX_ONES_IN_HINT,
        GAMMA1_RING_ELEMENT_SIZE,
        SIGNING_KEY_SIZE,
        SIGNATURE_SIZE,
    >(&signing_key.0, message, randomness)
}

/// Verify an ML-DSA-65 Signature
pub fn verify(
    verification_key: &MLDSA65VerificationKey,
    message: &[u8],
    signature: &MLDSA65Signature,
) -> Result<(), VerificationError> {
    crate::ml_dsa_generic::verify::<
        SIMDUnit,
        Shake128,
        Shake256,
        ROWS_IN_A,
        COLUMNS_IN_A,
        SIGNATURE_SIZE,
        VERIFICATION_KEY_SIZE,
        GAMMA1_EXPONENT,
        GAMMA1_RING_ELEMENT_SIZE,
        GAMMA2,
        BETA,
        COMMITMENT_RING_ELEMENT_SIZE,
        COMMITMENT_VECTOR_SIZE,
        COMMITMENT_HASH_SIZE,
        ONES_IN_VERIFIER_CHALLENGE,
        MAX_ONES_IN_HINT,
    >(&verification_key.0, message, &signature.0)
}
