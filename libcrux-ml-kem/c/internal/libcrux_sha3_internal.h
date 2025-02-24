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

#ifndef __internal_libcrux_sha3_internal_H
#define __internal_libcrux_sha3_internal_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "../libcrux_sha3_internal.h"
#include "eurydice_glue.h"

typedef libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t
    libcrux_sha3_portable_KeccakState;

static KRML_MUSTINLINE
    libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t
    libcrux_sha3_portable_incremental_shake128_init(void) {
  return libcrux_sha3_generic_keccak__libcrux_sha3__generic_keccak__KeccakState_T__N__TraitClause_0__1__new__uint64_t_1size_t();
}

static KRML_MUSTINLINE void
libcrux_sha3_portable_incremental_shake128_absorb_final(
    libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t *s,
    Eurydice_slice data0) {
  Eurydice_slice buf[1U] = {data0};
  libcrux_sha3_generic_keccak_absorb_final__uint64_t_1size_t_168size_t_31uint8_t(
      s, buf);
}

static KRML_MUSTINLINE void
libcrux_sha3_portable_incremental_shake128_squeeze_next_block(
    libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t *s,
    Eurydice_slice out0) {
  Eurydice_slice buf[1U] = {out0};
  libcrux_sha3_generic_keccak_squeeze_next_block__uint64_t_1size_t_168size_t(
      s, buf);
}

static KRML_MUSTINLINE void
libcrux_sha3_generic_keccak_squeeze_first_three_blocks__uint64_t_1size_t_168size_t(
    libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t *s,
    Eurydice_slice out[1U]) {
  K___Eurydice_slice_uint8_t_1size_t__Eurydice_slice_uint8_t_1size_t_ uu____0 =
      libcrux_sha3_portable_keccak___libcrux_sha3__traits__internal__KeccakItem_1__usize__for_u64___split_at_mut_n(
          out, (size_t)168U);
  Eurydice_slice o0[1U];
  memcpy(o0, uu____0.fst, (size_t)1U * sizeof(Eurydice_slice));
  Eurydice_slice o10[1U];
  memcpy(o10, uu____0.snd, (size_t)1U * sizeof(Eurydice_slice));
  libcrux_sha3_generic_keccak_squeeze_first_block__uint64_t_1size_t_168size_t(
      s, o0);
  K___Eurydice_slice_uint8_t_1size_t__Eurydice_slice_uint8_t_1size_t_ uu____1 =
      libcrux_sha3_portable_keccak___libcrux_sha3__traits__internal__KeccakItem_1__usize__for_u64___split_at_mut_n(
          o10, (size_t)168U);
  Eurydice_slice o1[1U];
  memcpy(o1, uu____1.fst, (size_t)1U * sizeof(Eurydice_slice));
  Eurydice_slice o2[1U];
  memcpy(o2, uu____1.snd, (size_t)1U * sizeof(Eurydice_slice));
  libcrux_sha3_generic_keccak_squeeze_next_block__uint64_t_1size_t_168size_t(
      s, o1);
  libcrux_sha3_generic_keccak_squeeze_next_block__uint64_t_1size_t_168size_t(
      s, o2);
}

static KRML_MUSTINLINE void
libcrux_sha3_portable_incremental_shake128_squeeze_first_three_blocks(
    libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t *s,
    Eurydice_slice out0) {
  Eurydice_slice buf[1U] = {out0};
  libcrux_sha3_generic_keccak_squeeze_first_three_blocks__uint64_t_1size_t_168size_t(
      s, buf);
}

#define libcrux_sha3_Sha224 0
#define libcrux_sha3_Sha256 1
#define libcrux_sha3_Sha384 2
#define libcrux_sha3_Sha512 3

typedef uint8_t libcrux_sha3_Algorithm;

static inline size_t libcrux_sha3_digest_size(libcrux_sha3_Algorithm mode) {
  size_t uu____0;
  switch (mode) {
    case libcrux_sha3_Sha224: {
      uu____0 = (size_t)28U;
      break;
    }
    case libcrux_sha3_Sha256: {
      uu____0 = (size_t)32U;
      break;
    }
    case libcrux_sha3_Sha384: {
      uu____0 = (size_t)48U;
      break;
    }
    case libcrux_sha3_Sha512: {
      uu____0 = (size_t)64U;
      break;
    }
    default: {
      KRML_HOST_EPRINTF("KaRaMeL incomplete match at %s:%d\n", __FILE__,
                        __LINE__);
      KRML_HOST_EXIT(253U);
    }
  }
  return uu____0;
}

static const size_t libcrux_sha3_generic_keccak__PI[24U] = {
    (size_t)6U, (size_t)12U, (size_t)18U, (size_t)24U, (size_t)3U,
    (size_t)9U, (size_t)10U, (size_t)16U, (size_t)22U, (size_t)1U,
    (size_t)7U, (size_t)13U, (size_t)19U, (size_t)20U, (size_t)4U,
    (size_t)5U, (size_t)11U, (size_t)17U, (size_t)23U, (size_t)2U,
    (size_t)8U, (size_t)14U, (size_t)15U, (size_t)21U};

static const size_t libcrux_sha3_generic_keccak__ROTC[24U] = {
    (size_t)1U,  (size_t)62U, (size_t)28U, (size_t)27U, (size_t)36U,
    (size_t)44U, (size_t)6U,  (size_t)55U, (size_t)20U, (size_t)3U,
    (size_t)10U, (size_t)43U, (size_t)25U, (size_t)39U, (size_t)41U,
    (size_t)45U, (size_t)15U, (size_t)21U, (size_t)8U,  (size_t)18U,
    (size_t)2U,  (size_t)61U, (size_t)56U, (size_t)14U};

static KRML_MUSTINLINE void
libcrux_sha3_generic_keccak_squeeze_first_five_blocks__uint64_t_1size_t_168size_t(
    libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t *s,
    Eurydice_slice out[1U]) {
  K___Eurydice_slice_uint8_t_1size_t__Eurydice_slice_uint8_t_1size_t_ uu____0 =
      libcrux_sha3_portable_keccak___libcrux_sha3__traits__internal__KeccakItem_1__usize__for_u64___split_at_mut_n(
          out, (size_t)168U);
  Eurydice_slice o0[1U];
  memcpy(o0, uu____0.fst, (size_t)1U * sizeof(Eurydice_slice));
  Eurydice_slice o10[1U];
  memcpy(o10, uu____0.snd, (size_t)1U * sizeof(Eurydice_slice));
  libcrux_sha3_generic_keccak_squeeze_first_block__uint64_t_1size_t_168size_t(
      s, o0);
  K___Eurydice_slice_uint8_t_1size_t__Eurydice_slice_uint8_t_1size_t_ uu____1 =
      libcrux_sha3_portable_keccak___libcrux_sha3__traits__internal__KeccakItem_1__usize__for_u64___split_at_mut_n(
          o10, (size_t)168U);
  Eurydice_slice o1[1U];
  memcpy(o1, uu____1.fst, (size_t)1U * sizeof(Eurydice_slice));
  Eurydice_slice o20[1U];
  memcpy(o20, uu____1.snd, (size_t)1U * sizeof(Eurydice_slice));
  libcrux_sha3_generic_keccak_squeeze_next_block__uint64_t_1size_t_168size_t(
      s, o1);
  K___Eurydice_slice_uint8_t_1size_t__Eurydice_slice_uint8_t_1size_t_ uu____2 =
      libcrux_sha3_portable_keccak___libcrux_sha3__traits__internal__KeccakItem_1__usize__for_u64___split_at_mut_n(
          o20, (size_t)168U);
  Eurydice_slice o2[1U];
  memcpy(o2, uu____2.fst, (size_t)1U * sizeof(Eurydice_slice));
  Eurydice_slice o30[1U];
  memcpy(o30, uu____2.snd, (size_t)1U * sizeof(Eurydice_slice));
  libcrux_sha3_generic_keccak_squeeze_next_block__uint64_t_1size_t_168size_t(
      s, o2);
  K___Eurydice_slice_uint8_t_1size_t__Eurydice_slice_uint8_t_1size_t_ uu____3 =
      libcrux_sha3_portable_keccak___libcrux_sha3__traits__internal__KeccakItem_1__usize__for_u64___split_at_mut_n(
          o30, (size_t)168U);
  Eurydice_slice o3[1U];
  memcpy(o3, uu____3.fst, (size_t)1U * sizeof(Eurydice_slice));
  Eurydice_slice o4[1U];
  memcpy(o4, uu____3.snd, (size_t)1U * sizeof(Eurydice_slice));
  libcrux_sha3_generic_keccak_squeeze_next_block__uint64_t_1size_t_168size_t(
      s, o3);
  libcrux_sha3_generic_keccak_squeeze_next_block__uint64_t_1size_t_168size_t(
      s, o4);
}

static KRML_MUSTINLINE void
libcrux_sha3_portable_incremental_shake128_squeeze_first_five_blocks(
    libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t *s,
    Eurydice_slice out0) {
  Eurydice_slice buf[1U] = {out0};
  libcrux_sha3_generic_keccak_squeeze_first_five_blocks__uint64_t_1size_t_168size_t(
      s, buf);
}

static KRML_MUSTINLINE void
libcrux_sha3_portable_incremental_shake256_absorb_final(
    libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t *s,
    Eurydice_slice data0) {
  Eurydice_slice buf[1U] = {data0};
  libcrux_sha3_generic_keccak_absorb_final__uint64_t_1size_t_136size_t_31uint8_t(
      s, buf);
}

static KRML_MUSTINLINE
    libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t
    libcrux_sha3_portable_incremental_shake256_init(void) {
  return libcrux_sha3_generic_keccak__libcrux_sha3__generic_keccak__KeccakState_T__N__TraitClause_0__1__new__uint64_t_1size_t();
}

static KRML_MUSTINLINE void
libcrux_sha3_portable_incremental_shake256_squeeze_first_block(
    libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t *s,
    Eurydice_slice out0) {
  Eurydice_slice buf[1U] = {out0};
  libcrux_sha3_generic_keccak_squeeze_first_block__uint64_t_1size_t_136size_t(
      s, buf);
}

static KRML_MUSTINLINE void
libcrux_sha3_portable_incremental_shake256_squeeze_next_block(
    libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t *s,
    Eurydice_slice out0) {
  Eurydice_slice buf[1U] = {out0};
  libcrux_sha3_generic_keccak_squeeze_next_block__uint64_t_1size_t_136size_t(
      s, buf);
}

static inline libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t
libcrux_sha3_portable___core__clone__Clone_for_libcrux_sha3__portable__KeccakState___clone(
    libcrux_sha3_generic_keccak_KeccakState__uint64_t__1size_t *self) {
  return self[0U];
}

static inline uint32_t
libcrux_sha3___core__convert__From_libcrux_sha3__Algorithm__for_u32__1__from(
    libcrux_sha3_Algorithm v) {
  uint32_t uu____0;
  switch (v) {
    case libcrux_sha3_Sha224: {
      uu____0 = 1U;
      break;
    }
    case libcrux_sha3_Sha256: {
      uu____0 = 2U;
      break;
    }
    case libcrux_sha3_Sha384: {
      uu____0 = 3U;
      break;
    }
    case libcrux_sha3_Sha512: {
      uu____0 = 4U;
      break;
    }
    default: {
      KRML_HOST_EPRINTF("KaRaMeL incomplete match at %s:%d\n", __FILE__,
                        __LINE__);
      KRML_HOST_EXIT(253U);
    }
  }
  return uu____0;
}

static inline libcrux_sha3_Algorithm
libcrux_sha3___core__convert__From_u32__for_libcrux_sha3__Algorithm___from(
    uint32_t v) {
  libcrux_sha3_Algorithm uu____0;
  switch (v) {
    case 1U: {
      uu____0 = libcrux_sha3_Sha224;
      break;
    }
    case 2U: {
      uu____0 = libcrux_sha3_Sha256;
      break;
    }
    case 3U: {
      uu____0 = libcrux_sha3_Sha384;
      break;
    }
    case 4U: {
      uu____0 = libcrux_sha3_Sha512;
      break;
    }
    default: {
      KRML_HOST_EPRINTF("KaRaMeL abort at %s:%d\n%s\n", __FILE__, __LINE__,
                        "panic!");
      KRML_HOST_EXIT(255U);
    }
  }
  return uu____0;
}

typedef uint8_t libcrux_sha3_Sha3_512Digest[64U];

typedef uint8_t libcrux_sha3_Sha3_384Digest[48U];

typedef uint8_t libcrux_sha3_Sha3_256Digest[32U];

typedef uint8_t libcrux_sha3_Sha3_224Digest[28U];

#if defined(__cplusplus)
}
#endif

#define __internal_libcrux_sha3_internal_H_DEFINED
#endif
