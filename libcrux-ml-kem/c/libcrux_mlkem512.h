/* 
  This file was generated by KaRaMeL <https://github.com/FStarLang/karamel>
  KaRaMeL invocation: /Users/jonathan/Code/eurydice/eurydice --config ../c.yaml ../../libcrux_ml_kem.llbc ../../libcrux_sha3.llbc
  F* version: 58c915a8
  KaRaMeL version: 04cb86b9
 */

#ifndef __libcrux_mlkem512_H
#define __libcrux_mlkem512_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "libcrux_sha3.h"
#include "libcrux_polynomial.h"
#include "libcrux_platform.h"
#include "libcrux_core.h"
#include "eurydice_glue.h"

#define LIBCRUX_ML_KEM_MLKEM512_VECTOR_U_COMPRESSION_FACTOR_512 ((size_t)10U)

#define LIBCRUX_ML_KEM_MLKEM512_C1_BLOCK_SIZE_512 (LIBCRUX_ML_KEM_CONSTANTS_COEFFICIENTS_IN_RING_ELEMENT * LIBCRUX_ML_KEM_MLKEM512_VECTOR_U_COMPRESSION_FACTOR_512 / (size_t)8U)

#define LIBCRUX_ML_KEM_MLKEM512_RANK_512 ((size_t)2U)

#define LIBCRUX_ML_KEM_MLKEM512_C1_SIZE_512 (LIBCRUX_ML_KEM_MLKEM512_C1_BLOCK_SIZE_512 * LIBCRUX_ML_KEM_MLKEM512_RANK_512)

#define LIBCRUX_ML_KEM_MLKEM512_VECTOR_V_COMPRESSION_FACTOR_512 ((size_t)4U)

#define LIBCRUX_ML_KEM_MLKEM512_C2_SIZE_512 (LIBCRUX_ML_KEM_CONSTANTS_COEFFICIENTS_IN_RING_ELEMENT * LIBCRUX_ML_KEM_MLKEM512_VECTOR_V_COMPRESSION_FACTOR_512 / (size_t)8U)

#define LIBCRUX_ML_KEM_MLKEM512_CPA_PKE_CIPHERTEXT_SIZE_512 (LIBCRUX_ML_KEM_MLKEM512_C1_SIZE_512 + LIBCRUX_ML_KEM_MLKEM512_C2_SIZE_512)

#define LIBCRUX_ML_KEM_MLKEM512_T_AS_NTT_ENCODED_SIZE_512 (LIBCRUX_ML_KEM_MLKEM512_RANK_512 * LIBCRUX_ML_KEM_CONSTANTS_COEFFICIENTS_IN_RING_ELEMENT * LIBCRUX_ML_KEM_CONSTANTS_BITS_PER_COEFFICIENT / (size_t)8U)

#define LIBCRUX_ML_KEM_MLKEM512_CPA_PKE_PUBLIC_KEY_SIZE_512 (LIBCRUX_ML_KEM_MLKEM512_T_AS_NTT_ENCODED_SIZE_512 + (size_t)32U)

#define LIBCRUX_ML_KEM_MLKEM512_CPA_PKE_SECRET_KEY_SIZE_512 (LIBCRUX_ML_KEM_MLKEM512_RANK_512 * LIBCRUX_ML_KEM_CONSTANTS_COEFFICIENTS_IN_RING_ELEMENT * LIBCRUX_ML_KEM_CONSTANTS_BITS_PER_COEFFICIENT / (size_t)8U)

#define LIBCRUX_ML_KEM_MLKEM512_ETA1 ((size_t)3U)

#define LIBCRUX_ML_KEM_MLKEM512_ETA1_RANDOMNESS_SIZE (LIBCRUX_ML_KEM_MLKEM512_ETA1 * (size_t)64U)

#define LIBCRUX_ML_KEM_MLKEM512_ETA2 ((size_t)2U)

#define LIBCRUX_ML_KEM_MLKEM512_ETA2_RANDOMNESS_SIZE (LIBCRUX_ML_KEM_MLKEM512_ETA2 * (size_t)64U)

#define LIBCRUX_ML_KEM_MLKEM512_IMPLICIT_REJECTION_HASH_INPUT_SIZE (LIBCRUX_ML_KEM_CONSTANTS_SHARED_SECRET_SIZE + LIBCRUX_ML_KEM_MLKEM512_CPA_PKE_CIPHERTEXT_SIZE_512)

#define LIBCRUX_ML_KEM_MLKEM512_RANKED_BYTES_PER_RING_ELEMENT_512 (LIBCRUX_ML_KEM_MLKEM512_RANK_512 * LIBCRUX_ML_KEM_CONSTANTS_BITS_PER_RING_ELEMENT / (size_t)8U)

#define LIBCRUX_ML_KEM_MLKEM512_SECRET_KEY_SIZE_512 (LIBCRUX_ML_KEM_MLKEM512_CPA_PKE_SECRET_KEY_SIZE_512 + LIBCRUX_ML_KEM_MLKEM512_CPA_PKE_PUBLIC_KEY_SIZE_512 + LIBCRUX_ML_KEM_CONSTANTS_H_DIGEST_SIZE + LIBCRUX_ML_KEM_CONSTANTS_SHARED_SECRET_SIZE)

void
libcrux_ml_kem_hash_functions_portable___libcrux_ml_kem__hash_functions__Hash_K__for_libcrux_ml_kem__hash_functions__portable__PortableHash_K____G___2size_t(
  Eurydice_slice input,
  uint8_t ret[64U]
);

void
libcrux_ml_kem_hash_functions_portable___libcrux_ml_kem__hash_functions__Hash_K__for_libcrux_ml_kem__hash_functions__portable__PortableHash_K____PRF___2size_t_32size_t(
  Eurydice_slice input,
  uint8_t ret[32U]
);

typedef struct libcrux_ml_kem_hash_functions_portable_PortableHash____2size_t_s
{ libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t shake128_state[2U]; }
libcrux_ml_kem_hash_functions_portable_PortableHash____2size_t;

libcrux_ml_kem_hash_functions_portable_PortableHash____2size_t
libcrux_ml_kem_hash_functions_portable___libcrux_ml_kem__hash_functions__Hash_K__for_libcrux_ml_kem__hash_functions__portable__PortableHash_K____shake128_init_absorb___2size_t(
  uint8_t input[2U][34U]
);

void
libcrux_ml_kem_hash_functions_portable___libcrux_ml_kem__hash_functions__Hash_K__for_libcrux_ml_kem__hash_functions__portable__PortableHash_K____shake128_squeeze_three_blocks___2size_t(
  libcrux_ml_kem_hash_functions_portable_PortableHash____2size_t *self,
  uint8_t ret[2U][504U]
);

void
libcrux_ml_kem_hash_functions_portable___libcrux_ml_kem__hash_functions__Hash_K__for_libcrux_ml_kem__hash_functions__portable__PortableHash_K____shake128_squeeze_block___2size_t(
  libcrux_ml_kem_hash_functions_portable_PortableHash____2size_t *self,
  uint8_t ret[2U][168U]
);

void
libcrux_ml_kem_hash_functions_portable___libcrux_ml_kem__hash_functions__Hash_K__for_libcrux_ml_kem__hash_functions__portable__PortableHash_K____PRFxN___2size_t_192size_t(
  uint8_t (*input)[33U],
  uint8_t ret[2U][192U]
);

void
libcrux_ml_kem_hash_functions_portable___libcrux_ml_kem__hash_functions__Hash_K__for_libcrux_ml_kem__hash_functions__portable__PortableHash_K____PRFxN___2size_t_128size_t(
  uint8_t (*input)[33U],
  uint8_t ret[2U][128U]
);

void
libcrux_ml_kem_hash_functions_portable___libcrux_ml_kem__hash_functions__Hash_K__for_libcrux_ml_kem__hash_functions__portable__PortableHash_K____PRF___2size_t_128size_t(
  Eurydice_slice input,
  uint8_t ret[128U]
);

void
libcrux_ml_kem_mlkem512_decapsulate(
  libcrux_ml_kem_types_MlKemPrivateKey____1632size_t *private_key,
  libcrux_ml_kem_types_MlKemCiphertext____768size_t *ciphertext,
  uint8_t ret[32U]
);

void
libcrux_ml_kem_hash_functions_portable___libcrux_ml_kem__hash_functions__Hash_K__for_libcrux_ml_kem__hash_functions__portable__PortableHash_K____H___2size_t(
  Eurydice_slice input,
  uint8_t ret[32U]
);

K___libcrux_ml_kem_types_MlKemCiphertext___768size_t___uint8_t_32size_t_
libcrux_ml_kem_mlkem512_encapsulate(
  libcrux_ml_kem_types_MlKemPublicKey____800size_t *public_key,
  uint8_t randomness[32U]
);

libcrux_ml_kem_types_MlKemKeyPair____1632size_t__800size_t
libcrux_ml_kem_mlkem512_generate_key_pair(uint8_t randomness[64U]);

core_option_Option__libcrux_ml_kem_types_MlKemPublicKey___800size_t__
libcrux_ml_kem_mlkem512_validate_public_key(
  libcrux_ml_kem_types_MlKemPublicKey____800size_t public_key
);

#if defined(__cplusplus)
}
#endif

#define __libcrux_mlkem512_H_DEFINED
#endif
