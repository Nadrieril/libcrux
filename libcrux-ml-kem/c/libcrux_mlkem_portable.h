/*
  This file was generated by KaRaMeL <https://github.com/FStarLang/karamel>
  KaRaMeL invocation: /Users/jonathan/Code/eurydice/eurydice --config ../c.yaml
  ../../libcrux_ml_kem.llbc ../../libcrux_sha3.llbc F* version: 58c915a8 KaRaMeL
  version: 22425a93
 */

#ifndef __libcrux_mlkem_portable_H
#define __libcrux_mlkem_portable_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "eurydice_glue.h"
#include "libcrux_core.h"
#include "libcrux_sha3.h"
#include "libcrux_sha3_internal.h"

#define LIBCRUX_ML_KEM_VECTOR_TRAITS_FIELD_ELEMENTS_IN_VECTOR ((size_t)16U)

#define LIBCRUX_ML_KEM_VECTOR_TRAITS_FIELD_MODULUS ((int16_t)3329)

#define LIBCRUX_ML_KEM_VECTOR_TRAITS_MONTGOMERY_R_SQUARED_MOD_FIELD_MODULUS \
  ((int16_t)1353)

#define LIBCRUX_ML_KEM_VECTOR_TRAITS_INVERSE_OF_MODULUS_MOD_MONTGOMERY_R \
  (62209U)

extern const uint8_t
    libcrux_ml_kem_vector_rej_sample_table_REJECTION_SAMPLE_SHUFFLE_TABLE[256U]
                                                                         [16U];

typedef struct libcrux_ml_kem_vector_portable_PortableVector_s {
  int16_t elements[16U];
} libcrux_ml_kem_vector_portable_PortableVector;

libcrux_ml_kem_vector_portable_PortableVector libcrux_ml_kem_vector_zero(void);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___ZERO(
    void);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_from_i16_array(Eurydice_slice array);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___from_i16_array(
    Eurydice_slice array);

libcrux_ml_kem_vector_portable_PortableVector libcrux_ml_kem_vector_add(
    libcrux_ml_kem_vector_portable_PortableVector lhs,
    libcrux_ml_kem_vector_portable_PortableVector *rhs);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___add(
    libcrux_ml_kem_vector_portable_PortableVector lhs,
    libcrux_ml_kem_vector_portable_PortableVector *rhs);

libcrux_ml_kem_vector_portable_PortableVector libcrux_ml_kem_vector_sub(
    libcrux_ml_kem_vector_portable_PortableVector lhs,
    libcrux_ml_kem_vector_portable_PortableVector *rhs);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___sub(
    libcrux_ml_kem_vector_portable_PortableVector lhs,
    libcrux_ml_kem_vector_portable_PortableVector *rhs);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_multiply_by_constant(
    libcrux_ml_kem_vector_portable_PortableVector v, int16_t c);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___multiply_by_constant(
    libcrux_ml_kem_vector_portable_PortableVector v, int16_t c);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_bitwise_and_with_constant(
    libcrux_ml_kem_vector_portable_PortableVector v, int16_t c);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___bitwise_and_with_constant(
    libcrux_ml_kem_vector_portable_PortableVector v, int16_t c);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_cond_subtract_3329(
    libcrux_ml_kem_vector_portable_PortableVector v);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___cond_subtract_3329(
    libcrux_ml_kem_vector_portable_PortableVector v);

#define LIBCRUX_ML_KEM_VECTOR_BARRETT_MULTIPLIER ((int32_t)20159)

#define LIBCRUX_ML_KEM_VECTOR_BARRETT_SHIFT ((int32_t)26)

#define LIBCRUX_ML_KEM_VECTOR_BARRETT_R \
  ((int32_t)1 << (uint32_t)LIBCRUX_ML_KEM_VECTOR_BARRETT_SHIFT)

int16_t libcrux_ml_kem_vector_barrett_reduce_element(int16_t value);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_barrett_reduce(
    libcrux_ml_kem_vector_portable_PortableVector v);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___barrett_reduce(
    libcrux_ml_kem_vector_portable_PortableVector v);

#define LIBCRUX_ML_KEM_VECTOR_MONTGOMERY_SHIFT (16U)

#define LIBCRUX_ML_KEM_VECTOR_MONTGOMERY_R \
  ((int32_t)1 << (uint32_t)LIBCRUX_ML_KEM_VECTOR_MONTGOMERY_SHIFT)

int16_t libcrux_ml_kem_vector_montgomery_reduce_element(int32_t value);

int16_t libcrux_ml_kem_vector_montgomery_multiply_fe_by_fer(int16_t fe,
                                                            int16_t fer);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_montgomery_multiply_by_constant(
    libcrux_ml_kem_vector_portable_PortableVector v, int16_t c);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___montgomery_multiply_by_constant(
    libcrux_ml_kem_vector_portable_PortableVector v, int16_t r);

uint8_t libcrux_ml_kem_vector_compress_message_coefficient(uint16_t fe);

libcrux_ml_kem_vector_portable_PortableVector libcrux_ml_kem_vector_compress_1(
    libcrux_ml_kem_vector_portable_PortableVector v);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___compress_1(
    libcrux_ml_kem_vector_portable_PortableVector v);

uint32_t libcrux_ml_kem_vector_get_n_least_significant_bits(uint8_t n,
                                                            uint32_t value);

int16_t libcrux_ml_kem_vector_compress_ciphertext_coefficient(
    uint8_t coefficient_bits, uint16_t fe);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_ntt_layer_1_step(
    libcrux_ml_kem_vector_portable_PortableVector v, int16_t zeta0,
    int16_t zeta1, int16_t zeta2, int16_t zeta3);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___ntt_layer_1_step(
    libcrux_ml_kem_vector_portable_PortableVector a, int16_t zeta0,
    int16_t zeta1, int16_t zeta2, int16_t zeta3);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_ntt_layer_2_step(
    libcrux_ml_kem_vector_portable_PortableVector v, int16_t zeta0,
    int16_t zeta1);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___ntt_layer_2_step(
    libcrux_ml_kem_vector_portable_PortableVector a, int16_t zeta0,
    int16_t zeta1);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_ntt_layer_3_step(
    libcrux_ml_kem_vector_portable_PortableVector v, int16_t zeta);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___ntt_layer_3_step(
    libcrux_ml_kem_vector_portable_PortableVector a, int16_t zeta);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_inv_ntt_layer_1_step(
    libcrux_ml_kem_vector_portable_PortableVector v, int16_t zeta0,
    int16_t zeta1, int16_t zeta2, int16_t zeta3);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___inv_ntt_layer_1_step(
    libcrux_ml_kem_vector_portable_PortableVector a, int16_t zeta0,
    int16_t zeta1, int16_t zeta2, int16_t zeta3);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_inv_ntt_layer_2_step(
    libcrux_ml_kem_vector_portable_PortableVector v, int16_t zeta0,
    int16_t zeta1);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___inv_ntt_layer_2_step(
    libcrux_ml_kem_vector_portable_PortableVector a, int16_t zeta0,
    int16_t zeta1);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_inv_ntt_layer_3_step(
    libcrux_ml_kem_vector_portable_PortableVector v, int16_t zeta);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___inv_ntt_layer_3_step(
    libcrux_ml_kem_vector_portable_PortableVector a, int16_t zeta);

typedef struct K___int16_t_int16_t_s {
  int16_t fst;
  int16_t snd;
} K___int16_t_int16_t;

K___int16_t_int16_t libcrux_ml_kem_vector_ntt_multiply_binomials(
    K___int16_t_int16_t _, K___int16_t_int16_t _0, int16_t zeta);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_ntt_multiply(
    libcrux_ml_kem_vector_portable_PortableVector *lhs,
    libcrux_ml_kem_vector_portable_PortableVector *rhs, int16_t zeta0,
    int16_t zeta1, int16_t zeta2, int16_t zeta3);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___ntt_multiply(
    libcrux_ml_kem_vector_portable_PortableVector *lhs,
    libcrux_ml_kem_vector_portable_PortableVector *rhs, int16_t zeta0,
    int16_t zeta1, int16_t zeta2, int16_t zeta3);

void libcrux_ml_kem_vector_serialize_1(
    libcrux_ml_kem_vector_portable_PortableVector v, uint8_t ret[2U]);

void libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___serialize_1(
    libcrux_ml_kem_vector_portable_PortableVector a, uint8_t ret[2U]);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_deserialize_1(Eurydice_slice v);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___deserialize_1(
    Eurydice_slice a);

void libcrux_ml_kem_vector_serialize_4(
    libcrux_ml_kem_vector_portable_PortableVector v, uint8_t ret[8U]);

void libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___serialize_4(
    libcrux_ml_kem_vector_portable_PortableVector a, uint8_t ret[8U]);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_deserialize_4(Eurydice_slice bytes);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___deserialize_4(
    Eurydice_slice a);

void libcrux_ml_kem_vector_serialize_5(
    libcrux_ml_kem_vector_portable_PortableVector v, uint8_t ret[10U]);

void libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___serialize_5(
    libcrux_ml_kem_vector_portable_PortableVector a, uint8_t ret[10U]);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_deserialize_5(Eurydice_slice bytes);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___deserialize_5(
    Eurydice_slice a);

void libcrux_ml_kem_vector_serialize_10(
    libcrux_ml_kem_vector_portable_PortableVector v, uint8_t ret[20U]);

void libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___serialize_10(
    libcrux_ml_kem_vector_portable_PortableVector a, uint8_t ret[20U]);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_deserialize_10(Eurydice_slice bytes);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___deserialize_10(
    Eurydice_slice a);

void libcrux_ml_kem_vector_serialize_11(
    libcrux_ml_kem_vector_portable_PortableVector v, uint8_t ret[22U]);

void libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___serialize_11(
    libcrux_ml_kem_vector_portable_PortableVector a, uint8_t ret[22U]);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_deserialize_11(Eurydice_slice bytes);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___deserialize_11(
    Eurydice_slice a);

void libcrux_ml_kem_vector_serialize_12(
    libcrux_ml_kem_vector_portable_PortableVector v, uint8_t ret[24U]);

void libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___serialize_12(
    libcrux_ml_kem_vector_portable_PortableVector a, uint8_t ret[24U]);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_deserialize_12(Eurydice_slice bytes);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___deserialize_12(
    Eurydice_slice a);

size_t libcrux_ml_kem_vector_rej_sample(Eurydice_slice a,
                                        Eurydice_slice result);

size_t
libcrux_ml_kem_vector___libcrux_ml_kem__vector__traits__Operations_for_libcrux_ml_kem__vector__portable__PortableVector___rej_sample(
    Eurydice_slice a, Eurydice_slice out);

libcrux_ml_kem_vector_portable_PortableVector
libcrux_ml_kem_vector_portable___core__clone__Clone_for_libcrux_ml_kem__vector__portable__PortableVector___clone(
    libcrux_ml_kem_vector_portable_PortableVector *self);

typedef struct
    libcrux_ml_kem_polynomial_PolynomialRingElement__libcrux_ml_kem_vector_portable_PortableVector_s {
  libcrux_ml_kem_vector_portable_PortableVector coefficients[16U];
} libcrux_ml_kem_polynomial_PolynomialRingElement__libcrux_ml_kem_vector_portable_PortableVector;

typedef struct
    libcrux_ml_kem_types_unpacked_MlKemPrivateKeyUnpacked__libcrux_ml_kem_vector_portable_PortableVector__3size_t_s {
  libcrux_ml_kem_polynomial_PolynomialRingElement__libcrux_ml_kem_vector_portable_PortableVector
      secret_as_ntt[3U];
} libcrux_ml_kem_types_unpacked_MlKemPrivateKeyUnpacked__libcrux_ml_kem_vector_portable_PortableVector__3size_t;

typedef struct
    libcrux_ml_kem_types_unpacked_MlKemPublicKeyUnpacked__libcrux_ml_kem_vector_portable_PortableVector__3size_t_s {
  libcrux_ml_kem_polynomial_PolynomialRingElement__libcrux_ml_kem_vector_portable_PortableVector
      t_as_ntt[3U];
  uint8_t seed_for_A[32U];
  libcrux_ml_kem_polynomial_PolynomialRingElement__libcrux_ml_kem_vector_portable_PortableVector
      A_transpose[3U][3U];
} libcrux_ml_kem_types_unpacked_MlKemPublicKeyUnpacked__libcrux_ml_kem_vector_portable_PortableVector__3size_t;

typedef struct
    libcrux_ml_kem_types_unpacked_MlKemKeyPairUnpacked__libcrux_ml_kem_vector_portable_PortableVector__3size_t_s {
  libcrux_ml_kem_types_unpacked_MlKemPrivateKeyUnpacked__libcrux_ml_kem_vector_portable_PortableVector__3size_t
      private_key;
  libcrux_ml_kem_types_unpacked_MlKemPublicKeyUnpacked__libcrux_ml_kem_vector_portable_PortableVector__3size_t
      public_key;
  uint8_t public_key_hash[32U];
  uint8_t implicit_rejection_value[32U];
} libcrux_ml_kem_types_unpacked_MlKemKeyPairUnpacked__libcrux_ml_kem_vector_portable_PortableVector__3size_t;

#if defined(__cplusplus)
}
#endif

#define __libcrux_mlkem_portable_H_DEFINED
#endif
