/*
  This file was generated by KaRaMeL <https://github.com/FStarLang/karamel>
  KaRaMeL invocation: /Users/bhargava/Desktop/repositories/eurydice/eurydice
  --config ../c.yaml ../../libcrux_ml_kem.llbc ../../libcrux_sha3.llbc F*
  version: 0e2a116d KaRaMeL version: 018dcd1d
 */

#ifndef __libcrux_sha3_neon_H
#define __libcrux_sha3_neon_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "eurydice_glue.h"
#include "intrinsics/libcrux_intrinsics_arm64.h"
#include "libcrux_core.h"
#include "libcrux_sha3_internal.h"

typedef struct
    libcrux_sha3_generic_keccak_KeccakState__core_core_arch_arm_shared_neon_uint64x2_t__2size_t_s {
  core_core_arch_arm_shared_neon_uint64x2_t st[5U][5U];
} libcrux_sha3_generic_keccak_KeccakState__core_core_arch_arm_shared_neon_uint64x2_t__2size_t;

void libcrux_sha3_neon_sha512(Eurydice_slice digest, Eurydice_slice data);

void libcrux_sha3_neon_sha256(Eurydice_slice digest, Eurydice_slice data);

void libcrux_sha3_neon_x2_shake256(Eurydice_slice input0, Eurydice_slice input1,
                                   Eurydice_slice out0, Eurydice_slice out1);

libcrux_sha3_generic_keccak_KeccakState__core_core_arch_arm_shared_neon_uint64x2_t__2size_t
libcrux_sha3_neon_x2_incremental_shake128_init(void);

void libcrux_sha3_neon_x2_incremental_shake128_absorb_final(
    libcrux_sha3_generic_keccak_KeccakState__core_core_arch_arm_shared_neon_uint64x2_t__2size_t
        *s,
    Eurydice_slice data0, Eurydice_slice data1);

void libcrux_sha3_neon_x2_incremental_shake128_squeeze_next_block(
    libcrux_sha3_generic_keccak_KeccakState__core_core_arch_arm_shared_neon_uint64x2_t__2size_t
        *s,
    Eurydice_slice out0, Eurydice_slice out1);

void libcrux_sha3_neon_x2_incremental_shake128_squeeze_first_three_blocks(
    libcrux_sha3_generic_keccak_KeccakState__core_core_arch_arm_shared_neon_uint64x2_t__2size_t
        *s,
    Eurydice_slice out0, Eurydice_slice out1);

void libcrux_sha3_neon_sha224(Eurydice_slice digest, Eurydice_slice data);

void libcrux_sha3_neon_sha384(Eurydice_slice digest, Eurydice_slice data);

#if defined(__cplusplus)
}
#endif

#define __libcrux_sha3_neon_H_DEFINED
#endif
