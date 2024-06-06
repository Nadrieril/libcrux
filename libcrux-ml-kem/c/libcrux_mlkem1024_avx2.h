/*
  This file was generated by KaRaMeL <https://github.com/FStarLang/karamel>
  KaRaMeL invocation: /home/franziskus/eurydice//eurydice --config ../c.yaml
  ../../libcrux_ml_kem.llbc ../../libcrux_sha3.llbc F* version: <unknown>
  KaRaMeL version: 40e3a603
 */

#ifndef __libcrux_mlkem1024_avx2_H
#define __libcrux_mlkem1024_avx2_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "eurydice_glue.h"
#include "libcrux_core.h"
#include "libcrux_mlkem512_avx2.h"

void libcrux_ml_kem_mlkem1024_avx2_decapsulate(
    libcrux_ml_kem_types_MlKemPrivateKey____3168size_t *private_key,
    libcrux_ml_kem_mlkem1024_MlKem1024Ciphertext *ciphertext, uint8_t ret[32U]);

K___libcrux_ml_kem_types_MlKemCiphertext___1568size_t___uint8_t_32size_t_
libcrux_ml_kem_mlkem1024_avx2_encapsulate(
    libcrux_ml_kem_types_MlKemPublicKey____1568size_t *public_key,
    uint8_t randomness[32U]);

libcrux_ml_kem_mlkem1024_MlKem1024KeyPair
libcrux_ml_kem_mlkem1024_avx2_generate_key_pair(uint8_t randomness[64U]);

core_option_Option__libcrux_ml_kem_types_MlKemPublicKey___1568size_t__
libcrux_ml_kem_mlkem1024_avx2_validate_public_key(
    libcrux_ml_kem_types_MlKemPublicKey____1568size_t public_key);

#if defined(__cplusplus)
}
#endif

#define __libcrux_mlkem1024_avx2_H_DEFINED
#endif
