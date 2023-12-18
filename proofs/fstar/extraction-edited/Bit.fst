module Bit
#set-options "--fuel 0 --ifuel 1 --z3rlimit 40"
open Core
open FStar.Mul

let get_bit_and _x _y _i = admit ()
let get_bit_or _x _y _i = admit ()
let get_bit_shl _x _y _i = admit ()
let get_bit_shr _x _y _i = admit ()

let pow2_minus_one_mod_lemma1 (n: nat) (m: nat {m < n})
   : Lemma (((pow2 n - 1) / pow2 m) % 2 == 1)
   = let d: pos = n - m in
     Math.Lemmas.pow2_plus m d;
     Math.Lemmas.lemma_div_plus (-1) (pow2 d) (pow2 m);
     if d > 0 then Math.Lemmas.pow2_double_mult (d-1)

let pow2_minus_one_mod_lemma2 (n: nat) (m: nat {n <= m})
  : Lemma (((pow2 n - 1) / pow2 m) % 2 == 0)
  = Math.Lemmas.pow2_le_compat m n;
    Math.Lemmas.small_div (pow2 n - 1) (pow2 m)

let get_bit_pow2_minus_one #t n nth
  = reveal_opaque (`%get_bit) (get_bit (mk_int #t (pow2 n - 1)) nth);
    if v nth < n then pow2_minus_one_mod_lemma1 n (v nth)
                 else pow2_minus_one_mod_lemma2 n (v nth)

let get_bit_pow2_minus_one_i32 x nth
  = let n = Some?.v (mask_inv_opt x) in
    mk_int_equiv_lemma #i32_inttype x;
    get_bit_pow2_minus_one #i32_inttype n nth

let get_bit_pow2_minus_one_u8 t x nth
  = let n = Some?.v (mask_inv_opt x) in
    mk_int_equiv_lemma #u8_inttype x;
    get_bit_pow2_minus_one #u8_inttype n nth

let get_bit_cast #t #u x nth
  = reveal_opaque (`%get_bit) (get_bit x nth);
    reveal_opaque (`%get_bit) (get_bit (cast x <: int_t u) nth);
    admit ()

let get_last_bit_signed_lemma #t x
  = admit ()
