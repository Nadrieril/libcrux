/*
 * SPDX-FileCopyrightText: 2024 Cryspen Sarl <info@cryspen.com>
 *
 * SPDX-License-Identifier: MIT or Apache-2.0
 *
 * This code was generated with the following revisions:
 * Charon: 920e78bb15250348a7a7a938e8023148e0a249bf
 * Eurydice: 4d6cf6308cb714aadcd1df0ba5f71977ec6c4a99
 * Karamel: 65aab550cf3ba36d52ae6ad1ad962bb573406395
 * F*: a32b316e521fa4f239b610ec8f1d15e78d62cbe8-dirty
 * Libcrux: c9c098bdea22047a1eb811ddf3468543855da224
 */

#ifndef __libcrux_core_H
#define __libcrux_core_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "eurydice_glue.h"

typedef struct core_ops_range_Range__size_t_s {
  size_t start;
  size_t end;
} core_ops_range_Range__size_t;

#define core_option_None 0
#define core_option_Some 1

typedef uint8_t core_option_Option__int32_t_tags;

typedef struct core_option_Option__size_t_s {
  core_option_Option__int32_t_tags tag;
  size_t f0;
} core_option_Option__size_t;

static inline uint16_t core_num__u16_7__wrapping_add(uint16_t x0, uint16_t x1);

#define CORE_NUM__U32_8__BITS (32U)

static inline uint64_t core_num__u64_9__from_le_bytes(uint8_t x0[8U]);

static inline void core_num__u64_9__to_le_bytes(uint64_t x0, uint8_t x1[8U]);

static inline uint32_t core_num__u8_6__count_ones(uint8_t x0);

static inline uint8_t core_num__u8_6__wrapping_sub(uint8_t x0, uint8_t x1);

#define LIBCRUX_ML_KEM_CONSTANTS_SHARED_SECRET_SIZE ((size_t)32U)

#define LIBCRUX_ML_KEM_CONSTANTS_BITS_PER_COEFFICIENT ((size_t)12U)

#define LIBCRUX_ML_KEM_CONSTANTS_COEFFICIENTS_IN_RING_ELEMENT ((size_t)256U)

#define LIBCRUX_ML_KEM_CONSTANTS_BITS_PER_RING_ELEMENT \
  (LIBCRUX_ML_KEM_CONSTANTS_COEFFICIENTS_IN_RING_ELEMENT * (size_t)12U)

#define LIBCRUX_ML_KEM_CONSTANTS_BYTES_PER_RING_ELEMENT \
  (LIBCRUX_ML_KEM_CONSTANTS_BITS_PER_RING_ELEMENT / (size_t)8U)

#define LIBCRUX_ML_KEM_CONSTANTS_CPA_PKE_KEY_GENERATION_SEED_SIZE ((size_t)32U)

#define LIBCRUX_ML_KEM_CONSTANTS_H_DIGEST_SIZE ((size_t)32U)

typedef struct libcrux_ml_kem_utils_extraction_helper_Keypair768_s {
  uint8_t fst[1152U];
  uint8_t snd[1184U];
} libcrux_ml_kem_utils_extraction_helper_Keypair768;

#define core_result_Ok 0
#define core_result_Err 1

typedef uint8_t
    core_result_Result__uint8_t_24size_t__core_array_TryFromSliceError_tags;

typedef struct
    core_result_Result__uint8_t_24size_t__core_array_TryFromSliceError_s {
  core_result_Result__uint8_t_24size_t__core_array_TryFromSliceError_tags tag;
  union {
    uint8_t case_Ok[24U];
    core_array_TryFromSliceError case_Err;
  } val;
} core_result_Result__uint8_t_24size_t__core_array_TryFromSliceError;

static inline void
core_result__core__result__Result_T__E___unwrap__uint8_t_24size_t__core_array_TryFromSliceError(
    core_result_Result__uint8_t_24size_t__core_array_TryFromSliceError self,
    uint8_t ret[24U]) {
  if (self.tag == core_result_Ok) {
    uint8_t f0[24U];
    memcpy(f0, self.val.case_Ok, (size_t)24U * sizeof(uint8_t));
    memcpy(ret, f0, (size_t)24U * sizeof(uint8_t));
  } else {
    KRML_HOST_EPRINTF("KaRaMeL abort at %s:%d\n%s\n", __FILE__, __LINE__,
                      "unwrap not Ok");
    KRML_HOST_EXIT(255U);
  }
}

typedef struct
    core_result_Result__uint8_t_20size_t__core_array_TryFromSliceError_s {
  core_result_Result__uint8_t_24size_t__core_array_TryFromSliceError_tags tag;
  union {
    uint8_t case_Ok[20U];
    core_array_TryFromSliceError case_Err;
  } val;
} core_result_Result__uint8_t_20size_t__core_array_TryFromSliceError;

static inline void
core_result__core__result__Result_T__E___unwrap__uint8_t_20size_t__core_array_TryFromSliceError(
    core_result_Result__uint8_t_20size_t__core_array_TryFromSliceError self,
    uint8_t ret[20U]) {
  if (self.tag == core_result_Ok) {
    uint8_t f0[20U];
    memcpy(f0, self.val.case_Ok, (size_t)20U * sizeof(uint8_t));
    memcpy(ret, f0, (size_t)20U * sizeof(uint8_t));
  } else {
    KRML_HOST_EPRINTF("KaRaMeL abort at %s:%d\n%s\n", __FILE__, __LINE__,
                      "unwrap not Ok");
    KRML_HOST_EXIT(255U);
  }
}

typedef struct
    core_result_Result__uint8_t_10size_t__core_array_TryFromSliceError_s {
  core_result_Result__uint8_t_24size_t__core_array_TryFromSliceError_tags tag;
  union {
    uint8_t case_Ok[10U];
    core_array_TryFromSliceError case_Err;
  } val;
} core_result_Result__uint8_t_10size_t__core_array_TryFromSliceError;

static inline void
core_result__core__result__Result_T__E___unwrap__uint8_t_10size_t__core_array_TryFromSliceError(
    core_result_Result__uint8_t_10size_t__core_array_TryFromSliceError self,
    uint8_t ret[10U]) {
  if (self.tag == core_result_Ok) {
    uint8_t f0[10U];
    memcpy(f0, self.val.case_Ok, (size_t)10U * sizeof(uint8_t));
    memcpy(ret, f0, (size_t)10U * sizeof(uint8_t));
  } else {
    KRML_HOST_EPRINTF("KaRaMeL abort at %s:%d\n%s\n", __FILE__, __LINE__,
                      "unwrap not Ok");
    KRML_HOST_EXIT(255U);
  }
}

typedef struct
    K___Eurydice_slice_uint8_t_4size_t__Eurydice_slice_uint8_t_4size_t__s {
  Eurydice_slice fst[4U];
  Eurydice_slice snd[4U];
} K___Eurydice_slice_uint8_t_4size_t__Eurydice_slice_uint8_t_4size_t_;

typedef struct libcrux_ml_kem_types_MlKemPublicKey____1184size_t_s {
  uint8_t value[1184U];
} libcrux_ml_kem_types_MlKemPublicKey____1184size_t;

typedef struct
    core_option_Option__libcrux_ml_kem_types_MlKemPublicKey___1184size_t___s {
  core_option_Option__int32_t_tags tag;
  libcrux_ml_kem_types_MlKemPublicKey____1184size_t f0;
} core_option_Option__libcrux_ml_kem_types_MlKemPublicKey___1184size_t__;

static inline libcrux_ml_kem_types_MlKemPublicKey____1184size_t
libcrux_ml_kem_types___core__convert__From__Array_u8__SIZE___for_libcrux_ml_kem__types__MlKemPublicKey_SIZE___14__from___1184size_t(
    uint8_t value[1184U]) {
  uint8_t uu____0[1184U];
  memcpy(uu____0, value, (size_t)1184U * sizeof(uint8_t));
  libcrux_ml_kem_types_MlKemPublicKey____1184size_t lit;
  memcpy(lit.value, uu____0, (size_t)1184U * sizeof(uint8_t));
  return lit;
}

typedef struct libcrux_ml_kem_types_MlKemPrivateKey____2400size_t_s {
  uint8_t value[2400U];
} libcrux_ml_kem_types_MlKemPrivateKey____2400size_t;

typedef struct libcrux_ml_kem_mlkem768_MlKem768KeyPair_s {
  libcrux_ml_kem_types_MlKemPrivateKey____2400size_t sk;
  libcrux_ml_kem_types_MlKemPublicKey____1184size_t pk;
} libcrux_ml_kem_mlkem768_MlKem768KeyPair;

static inline libcrux_ml_kem_mlkem768_MlKem768KeyPair
libcrux_ml_kem_types__libcrux_ml_kem__types__MlKemKeyPair_PRIVATE_KEY_SIZE__PUBLIC_KEY_SIZE___from___2400size_t_1184size_t(
    libcrux_ml_kem_types_MlKemPrivateKey____2400size_t sk,
    libcrux_ml_kem_types_MlKemPublicKey____1184size_t pk) {
  return (
      CLITERAL(libcrux_ml_kem_mlkem768_MlKem768KeyPair){.sk = sk, .pk = pk});
}

static inline libcrux_ml_kem_types_MlKemPrivateKey____2400size_t
libcrux_ml_kem_types___core__convert__From__Array_u8__SIZE___for_libcrux_ml_kem__types__MlKemPrivateKey_SIZE___8__from___2400size_t(
    uint8_t value[2400U]) {
  uint8_t uu____0[2400U];
  memcpy(uu____0, value, (size_t)2400U * sizeof(uint8_t));
  libcrux_ml_kem_types_MlKemPrivateKey____2400size_t lit;
  memcpy(lit.value, uu____0, (size_t)2400U * sizeof(uint8_t));
  return lit;
}

typedef struct libcrux_ml_kem_mlkem768_MlKem768Ciphertext_s {
  uint8_t value[1088U];
} libcrux_ml_kem_mlkem768_MlKem768Ciphertext;

typedef struct
    K___libcrux_ml_kem_types_MlKemCiphertext___1088size_t___uint8_t_32size_t__s {
  libcrux_ml_kem_mlkem768_MlKem768Ciphertext fst;
  uint8_t snd[32U];
} K___libcrux_ml_kem_types_MlKemCiphertext___1088size_t___uint8_t_32size_t_;

static inline libcrux_ml_kem_mlkem768_MlKem768Ciphertext
libcrux_ml_kem_types___core__convert__From__Array_u8__SIZE___for_libcrux_ml_kem__types__MlKemCiphertext_SIZE___2__from___1088size_t(
    uint8_t value[1088U]) {
  uint8_t uu____0[1088U];
  memcpy(uu____0, value, (size_t)1088U * sizeof(uint8_t));
  libcrux_ml_kem_mlkem768_MlKem768Ciphertext lit;
  memcpy(lit.value, uu____0, (size_t)1088U * sizeof(uint8_t));
  return lit;
}

static inline uint8_t *
libcrux_ml_kem_types__libcrux_ml_kem__types__MlKemPublicKey_SIZE__18__as_slice___1184size_t(
    libcrux_ml_kem_types_MlKemPublicKey____1184size_t *self) {
  return self->value;
}

static KRML_MUSTINLINE void libcrux_ml_kem_utils_into_padded_array___33size_t(
    Eurydice_slice slice, uint8_t ret[33U]) {
  uint8_t out[33U] = {0U};
  uint8_t *uu____0 = out;
  core_slice___Slice_T___copy_from_slice(
      Eurydice_array_to_subslice(
          (size_t)33U, uu____0,
          (CLITERAL(core_ops_range_Range__size_t){
              .start = (size_t)0U,
              .end = core_slice___Slice_T___len(slice, uint8_t, size_t)}),
          uint8_t, core_ops_range_Range__size_t, Eurydice_slice),
      slice, uint8_t, void *);
  memcpy(ret, out, (size_t)33U * sizeof(uint8_t));
}

typedef struct
    core_result_Result__uint8_t_32size_t__core_array_TryFromSliceError_s {
  core_result_Result__uint8_t_24size_t__core_array_TryFromSliceError_tags tag;
  union {
    uint8_t case_Ok[32U];
    core_array_TryFromSliceError case_Err;
  } val;
} core_result_Result__uint8_t_32size_t__core_array_TryFromSliceError;

static inline void
core_result__core__result__Result_T__E___unwrap__uint8_t_32size_t__core_array_TryFromSliceError(
    core_result_Result__uint8_t_32size_t__core_array_TryFromSliceError self,
    uint8_t ret[32U]) {
  if (self.tag == core_result_Ok) {
    uint8_t f0[32U];
    memcpy(f0, self.val.case_Ok, (size_t)32U * sizeof(uint8_t));
    memcpy(ret, f0, (size_t)32U * sizeof(uint8_t));
  } else {
    KRML_HOST_EPRINTF("KaRaMeL abort at %s:%d\n%s\n", __FILE__, __LINE__,
                      "unwrap not Ok");
    KRML_HOST_EXIT(255U);
  }
}

static KRML_MUSTINLINE void libcrux_ml_kem_utils_into_padded_array___34size_t(
    Eurydice_slice slice, uint8_t ret[34U]) {
  uint8_t out[34U] = {0U};
  uint8_t *uu____0 = out;
  core_slice___Slice_T___copy_from_slice(
      Eurydice_array_to_subslice(
          (size_t)34U, uu____0,
          (CLITERAL(core_ops_range_Range__size_t){
              .start = (size_t)0U,
              .end = core_slice___Slice_T___len(slice, uint8_t, size_t)}),
          uint8_t, core_ops_range_Range__size_t, Eurydice_slice),
      slice, uint8_t, void *);
  memcpy(ret, out, (size_t)34U * sizeof(uint8_t));
}

static inline Eurydice_slice
libcrux_ml_kem_types___core__convert__AsRef__Slice_u8___for_libcrux_ml_kem__types__MlKemCiphertext_SIZE___1__as_ref___1088size_t(
    libcrux_ml_kem_mlkem768_MlKem768Ciphertext *self) {
  return Eurydice_array_to_slice((size_t)1088U, self->value, uint8_t,
                                 Eurydice_slice);
}

static KRML_MUSTINLINE void libcrux_ml_kem_utils_into_padded_array___1120size_t(
    Eurydice_slice slice, uint8_t ret[1120U]) {
  uint8_t out[1120U] = {0U};
  uint8_t *uu____0 = out;
  core_slice___Slice_T___copy_from_slice(
      Eurydice_array_to_subslice(
          (size_t)1120U, uu____0,
          (CLITERAL(core_ops_range_Range__size_t){
              .start = (size_t)0U,
              .end = core_slice___Slice_T___len(slice, uint8_t, size_t)}),
          uint8_t, core_ops_range_Range__size_t, Eurydice_slice),
      slice, uint8_t, void *);
  memcpy(ret, out, (size_t)1120U * sizeof(uint8_t));
}

static KRML_MUSTINLINE void libcrux_ml_kem_utils_into_padded_array___64size_t(
    Eurydice_slice slice, uint8_t ret[64U]) {
  uint8_t out[64U] = {0U};
  uint8_t *uu____0 = out;
  core_slice___Slice_T___copy_from_slice(
      Eurydice_array_to_subslice(
          (size_t)64U, uu____0,
          (CLITERAL(core_ops_range_Range__size_t){
              .start = (size_t)0U,
              .end = core_slice___Slice_T___len(slice, uint8_t, size_t)}),
          uint8_t, core_ops_range_Range__size_t, Eurydice_slice),
      slice, uint8_t, void *);
  memcpy(ret, out, (size_t)64U * sizeof(uint8_t));
}

typedef struct
    core_result_Result__int16_t_16size_t__core_array_TryFromSliceError_s {
  core_result_Result__uint8_t_24size_t__core_array_TryFromSliceError_tags tag;
  union {
    int16_t case_Ok[16U];
    core_array_TryFromSliceError case_Err;
  } val;
} core_result_Result__int16_t_16size_t__core_array_TryFromSliceError;

static inline void
core_result__core__result__Result_T__E___unwrap__int16_t_16size_t__core_array_TryFromSliceError(
    core_result_Result__int16_t_16size_t__core_array_TryFromSliceError self,
    int16_t ret[16U]) {
  if (self.tag == core_result_Ok) {
    int16_t f0[16U];
    memcpy(f0, self.val.case_Ok, (size_t)16U * sizeof(int16_t));
    memcpy(ret, f0, (size_t)16U * sizeof(int16_t));
  } else {
    KRML_HOST_EPRINTF("KaRaMeL abort at %s:%d\n%s\n", __FILE__, __LINE__,
                      "unwrap not Ok");
    KRML_HOST_EXIT(255U);
  }
}

typedef struct
    core_result_Result__uint8_t_8size_t__core_array_TryFromSliceError_s {
  core_result_Result__uint8_t_24size_t__core_array_TryFromSliceError_tags tag;
  union {
    uint8_t case_Ok[8U];
    core_array_TryFromSliceError case_Err;
  } val;
} core_result_Result__uint8_t_8size_t__core_array_TryFromSliceError;

static inline void
core_result__core__result__Result_T__E___unwrap__uint8_t_8size_t__core_array_TryFromSliceError(
    core_result_Result__uint8_t_8size_t__core_array_TryFromSliceError self,
    uint8_t ret[8U]) {
  if (self.tag == core_result_Ok) {
    uint8_t f0[8U];
    memcpy(f0, self.val.case_Ok, (size_t)8U * sizeof(uint8_t));
    memcpy(ret, f0, (size_t)8U * sizeof(uint8_t));
  } else {
    KRML_HOST_EPRINTF("KaRaMeL abort at %s:%d\n%s\n", __FILE__, __LINE__,
                      "unwrap not Ok");
    KRML_HOST_EXIT(255U);
  }
}

typedef struct K___Eurydice_slice_uint8_t_Eurydice_slice_uint8_t_s {
  Eurydice_slice fst;
  Eurydice_slice snd;
} K___Eurydice_slice_uint8_t_Eurydice_slice_uint8_t;

typedef struct
    K___Eurydice_slice_uint8_t_1size_t__Eurydice_slice_uint8_t_1size_t__s {
  Eurydice_slice fst[1U];
  Eurydice_slice snd[1U];
} K___Eurydice_slice_uint8_t_1size_t__Eurydice_slice_uint8_t_1size_t_;

#if defined(__cplusplus)
}
#endif

#define __libcrux_core_H_DEFINED
#endif
