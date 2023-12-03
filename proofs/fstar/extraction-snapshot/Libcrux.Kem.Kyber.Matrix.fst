module Libcrux.Kem.Kyber.Matrix
#set-options "--fuel 0 --ifuel 1 --z3rlimit 15"
open Core
open FStar.Mul

let compute_As_plus_e
      (v_K: usize)
      (matrix_A: t_Array (t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K) v_K)
      (s_as_ntt error_as_ntt: t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K)
    : t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
  assume (v_K >. sz 1 /\ v_K <=. sz 4);
  let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
    Rust_primitives.Hax.repeat Libcrux.Kem.Kyber.Arithmetic.impl__PolynomialRingElement__ZERO v_K
  in
  let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
    Core.Iter.Traits.Iterator.f_fold (Core.Iter.Traits.Collect.f_into_iter (Core.Iter.Traits.Iterator.f_enumerate
              (Core.Slice.impl__iter (Rust_primitives.unsize matrix_A
                    <:
                    t_Slice (t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K))
                <:
                Core.Slice.Iter.t_Iter
                (t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K))
            <:
            Core.Iter.Adapters.Enumerate.t_Enumerate
            (Core.Slice.Iter.t_Iter
              (t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K)))
        <:
        Core.Iter.Adapters.Enumerate.t_Enumerate
        (Core.Slice.Iter.t_Iter (t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K)))
      result
      (fun result temp_1_ ->
          let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K = result in
          let i, row:(usize & t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K) =
            temp_1_
          in
          assume (i <. v_K);
          let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
            Core.Iter.Traits.Iterator.f_fold (Core.Iter.Traits.Collect.f_into_iter (Core.Iter.Traits.Iterator.f_enumerate
                      (Core.Slice.impl__iter (Rust_primitives.unsize row
                            <:
                            t_Slice Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                        <:
                        Core.Slice.Iter.t_Iter Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                    <:
                    Core.Iter.Adapters.Enumerate.t_Enumerate
                    (Core.Slice.Iter.t_Iter Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement))
                <:
                Core.Iter.Adapters.Enumerate.t_Enumerate
                (Core.Slice.Iter.t_Iter Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement))
              result
              (fun result temp_1_ ->
                  let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
                    result
                  in
                  let j, matrix_element:(usize &
                    Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement) =
                    temp_1_
                  in
                  assume (j <. v_K);
                  let product:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
                    Libcrux.Kem.Kyber.Ntt.ntt_multiply matrix_element
                      (s_as_ntt.[ j ] <: Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                  in
                  let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
                    Rust_primitives.Hax.Monomorphized_update_at.update_at_usize result
                      i
                      (Libcrux.Kem.Kyber.Arithmetic.add_to_ring_element v_K
                          (result.[ i ] <: Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                          product
                        <:
                        Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                  in
                  result)
          in
          Core.Iter.Traits.Iterator.f_fold (Core.Iter.Traits.Collect.f_into_iter ({
                    Core.Ops.Range.f_start = sz 0;
                    Core.Ops.Range.f_end
                    =
                    Libcrux.Kem.Kyber.Constants.v_COEFFICIENTS_IN_RING_ELEMENT
                  }
                  <:
                  Core.Ops.Range.t_Range usize)
              <:
              Core.Ops.Range.t_Range usize)
            result
            (fun result j ->
                let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
                  result
                in
                let j:usize = j in
                let coefficient_normal_form:i32 =
                  Libcrux.Kem.Kyber.Arithmetic.to_standard_domain ((result.[ i ]
                        <:
                        Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                        .Libcrux.Kem.Kyber.Arithmetic.f_coefficients.[ j ]
                      <:
                      i32)
                in
                let x1: Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement = error_as_ntt.[i] in
                let x2 : i32 = x1.f_coefficients.[j] in
                assume (range (v coefficient_normal_form + v x2) i32_inttype);
                assume (Libcrux.Kem.Kyber.Arithmetic.barrett_pre (coefficient_normal_form +! x2));
                Rust_primitives.Hax.Monomorphized_update_at.update_at_usize result
                  i
                  ({
                      (result.[ i ] <: Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement) with
                      Libcrux.Kem.Kyber.Arithmetic.f_coefficients
                      =
                      Rust_primitives.Hax.Monomorphized_update_at.update_at_usize (result.[ i ]
                          <:
                          Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                          .Libcrux.Kem.Kyber.Arithmetic.f_coefficients
                        j
                        (Libcrux.Kem.Kyber.Arithmetic.barrett_reduce (coefficient_normal_form +!
                              ((error_as_ntt.[ i ]
                                  <:
                                  Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                                  .Libcrux.Kem.Kyber.Arithmetic.f_coefficients.[ j ]
                                <:
                                i32)
                              <:
                              i32)
                          <:
                          i32)
                      <:
                      t_Array i32 (sz 256)
                    }
                    <:
                    Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)))
  in
  result

let compute_message
      (v_K: usize)
      (v: Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
      (secret_as_ntt u_as_ntt: t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K)
    : Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
  assume (v_K >. sz 1 && v_K <=. sz 4);
  let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
    Libcrux.Kem.Kyber.Arithmetic.impl__PolynomialRingElement__ZERO
  in
  let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
    Core.Iter.Traits.Iterator.f_fold (Core.Iter.Traits.Collect.f_into_iter ({
              Core.Ops.Range.f_start = sz 0;
              Core.Ops.Range.f_end = v_K
            }
            <:
            Core.Ops.Range.t_Range usize)
        <:
        Core.Ops.Range.t_Range usize)
      result
      (fun result i ->
          let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement = result in
          let i:usize = i in
          let product:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
            Libcrux.Kem.Kyber.Ntt.ntt_multiply (secret_as_ntt.[ i ]
                <:
                Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
              (u_as_ntt.[ i ] <: Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
          in
          let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
            Libcrux.Kem.Kyber.Arithmetic.add_to_ring_element v_K result product
          in
          result)
  in
  let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
    Libcrux.Kem.Kyber.Ntt.invert_ntt_montgomery v_K result
  in
  let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
    Core.Iter.Traits.Iterator.f_fold (Core.Iter.Traits.Collect.f_into_iter ({
                                     Core.Ops.Range.f_start = sz 0;
              Core.Ops.Range.f_end = Libcrux.Kem.Kyber.Constants.v_COEFFICIENTS_IN_RING_ELEMENT
            }
            <:
            Core.Ops.Range.t_Range usize)
        <:
        Core.Ops.Range.t_Range usize)
      result
      (fun result i ->
          let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement = result in
          let i:usize = i in
          assume (range (Rust_primitives.Integers.v #i32_inttype ((result.f_coefficients).[i]) * 1441) i32_inttype);
          assume (Libcrux.Kem.Kyber.Arithmetic.montgomery_pre (result.f_coefficients.[i] *! 1441l));
          let coefficient_normal_form:i32 =
            Libcrux.Kem.Kyber.Arithmetic.montgomery_reduce ((result
                    .Libcrux.Kem.Kyber.Arithmetic.f_coefficients.[ i ]
                  <:
                  i32) *!
                1441l
                <:
                i32)
          in
          assume (range (Rust_primitives.Integers.v #i32_inttype ((v.f_coefficients).[i]) - Rust_primitives.Integers.v coefficient_normal_form) i32_inttype);
          assume (Libcrux.Kem.Kyber.Arithmetic.barrett_pre (v.f_coefficients.[i] -! coefficient_normal_form));
          let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
            {
              result with
              Libcrux.Kem.Kyber.Arithmetic.f_coefficients
              =
              Rust_primitives.Hax.Monomorphized_update_at.update_at_usize result
                  .Libcrux.Kem.Kyber.Arithmetic.f_coefficients
                i
                (Libcrux.Kem.Kyber.Arithmetic.barrett_reduce ((v
                          .Libcrux.Kem.Kyber.Arithmetic.f_coefficients.[ i ]
                        <:
                        i32) -!
                      coefficient_normal_form
                      <:
                      i32)
                  <:
                  i32)
            }
            <:
            Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement
          in
          result)
  in
  result

let compute_ring_element_v
      (v_K: usize)
      (tt_as_ntt r_as_ntt: t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K)
      (error_2_ message: Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
    : Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
  assume (v_K >. sz 1 && v_K <=. sz 4);
  let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
    Libcrux.Kem.Kyber.Arithmetic.impl__PolynomialRingElement__ZERO
  in
  let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
    Core.Iter.Traits.Iterator.f_fold (Core.Iter.Traits.Collect.f_into_iter ({
              Core.Ops.Range.f_start = sz 0;
              Core.Ops.Range.f_end = v_K
            }
            <:
            Core.Ops.Range.t_Range usize)
        <:
        Core.Ops.Range.t_Range usize)
      result
      (fun result i ->
          let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement = result in
          let i:usize = i in
          let product:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
            Libcrux.Kem.Kyber.Ntt.ntt_multiply (tt_as_ntt.[ i ]
                <:
                Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
              (r_as_ntt.[ i ] <: Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
          in
          let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
            Libcrux.Kem.Kyber.Arithmetic.add_to_ring_element v_K result product
          in
          result)
  in
  let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
    Libcrux.Kem.Kyber.Ntt.invert_ntt_montgomery v_K result
  in
  let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
    Core.Iter.Traits.Iterator.f_fold (Core.Iter.Traits.Collect.f_into_iter ({
              Core.Ops.Range.f_start = sz 0;
              Core.Ops.Range.f_end = Libcrux.Kem.Kyber.Constants.v_COEFFICIENTS_IN_RING_ELEMENT
            }
            <:
            Core.Ops.Range.t_Range usize)
        <:
        Core.Ops.Range.t_Range usize)
      result
      (fun result i ->
          let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement = result in
          let i:usize = i in
          assume (range (Rust_primitives.Integers.v #i32_inttype ((result.f_coefficients).[i]) * 1441) i32_inttype);
          assume (Libcrux.Kem.Kyber.Arithmetic.montgomery_pre (result.f_coefficients.[i] *! 1441l));
          let coefficient_normal_form:i32 =
            Libcrux.Kem.Kyber.Arithmetic.montgomery_reduce ((result
                    .Libcrux.Kem.Kyber.Arithmetic.f_coefficients.[ i ]
                  <:
                  i32) *!
                1441l
                <:
                i32)
          in
          assume (range (v coefficient_normal_form +
                        v #i32_inttype error_2_.f_coefficients.[ i ]) i32_inttype);
          assume (range (v coefficient_normal_form +
                        v #i32_inttype error_2_.f_coefficients.[ i ] +
                        v #i32_inttype message.f_coefficients.[ i ]) i32_inttype);
          assume (Libcrux.Kem.Kyber.Arithmetic.barrett_pre (coefficient_normal_form +! error_2_.f_coefficients.[ i ] +! message.f_coefficients.[ i ]));
          let result:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
            {
              result with
              Libcrux.Kem.Kyber.Arithmetic.f_coefficients
              =
              Rust_primitives.Hax.Monomorphized_update_at.update_at_usize result
                  .Libcrux.Kem.Kyber.Arithmetic.f_coefficients
                i
                (Libcrux.Kem.Kyber.Arithmetic.barrett_reduce ((coefficient_normal_form +!
                        (error_2_.Libcrux.Kem.Kyber.Arithmetic.f_coefficients.[ i ] <: i32)
                        <:
                        i32) +!
                      (message.Libcrux.Kem.Kyber.Arithmetic.f_coefficients.[ i ] <: i32)
                      <:
                      i32)
                  <:
                  i32)
            }
            <:
            Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement
          in
          result)
  in
  result

let compute_vector_u
      (v_K: usize)
      (a_as_ntt: t_Array (t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K) v_K)
      (r_as_ntt error_1_: t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K)
    : t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
  assume (v_K >. sz 1 && v_K <=. sz 4);
  let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
    Rust_primitives.Hax.repeat Libcrux.Kem.Kyber.Arithmetic.impl__PolynomialRingElement__ZERO v_K
  in
  let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
    Core.Iter.Traits.Iterator.f_fold (Core.Iter.Traits.Collect.f_into_iter (Core.Iter.Traits.Iterator.f_enumerate
              (Core.Slice.impl__iter (Rust_primitives.unsize a_as_ntt
                    <:
                    t_Slice (t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K))
                <:
                Core.Slice.Iter.t_Iter
                (t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K))
            <:
            Core.Iter.Adapters.Enumerate.t_Enumerate
            (Core.Slice.Iter.t_Iter
              (t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K)))
        <:
        Core.Iter.Adapters.Enumerate.t_Enumerate
        (Core.Slice.Iter.t_Iter (t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K)))
      result
      (fun result temp_1_ ->
          let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K = result in
          let i, row:(usize & t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K) =
            temp_1_
          in
          assume (i <. v_K);
          let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
            Core.Iter.Traits.Iterator.f_fold (Core.Iter.Traits.Collect.f_into_iter (Core.Iter.Traits.Iterator.f_enumerate
                      (Core.Slice.impl__iter (Rust_primitives.unsize row
                            <:
                            t_Slice Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                        <:
                        Core.Slice.Iter.t_Iter Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                    <:
                    Core.Iter.Adapters.Enumerate.t_Enumerate
                    (Core.Slice.Iter.t_Iter Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement))
                <:
                Core.Iter.Adapters.Enumerate.t_Enumerate
                (Core.Slice.Iter.t_Iter Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement))
              result
              (fun result temp_1_ ->
                  let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
                    result
                  in
                  let j, a_element:(usize & Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement) =
                    temp_1_
                  in
                  assume (j <. v_K);
                  let product:Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement =
                    Libcrux.Kem.Kyber.Ntt.ntt_multiply a_element
                      (r_as_ntt.[ j ] <: Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                  in
                  let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
                    Rust_primitives.Hax.Monomorphized_update_at.update_at_usize result
                      i
                      (Libcrux.Kem.Kyber.Arithmetic.add_to_ring_element v_K
                          (result.[ i ] <: Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                          product
                        <:
                        Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                  in
                  result)
          in
          let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
            Rust_primitives.Hax.Monomorphized_update_at.update_at_usize result
              i
              (Libcrux.Kem.Kyber.Ntt.invert_ntt_montgomery v_K
                  (result.[ i ] <: Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                <:
                Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
          in
          Core.Iter.Traits.Iterator.f_fold (Core.Iter.Traits.Collect.f_into_iter ({
                    Core.Ops.Range.f_start = sz 0;
                    Core.Ops.Range.f_end
                    =
                    Libcrux.Kem.Kyber.Constants.v_COEFFICIENTS_IN_RING_ELEMENT
                  }
                  <:
                  Core.Ops.Range.t_Range usize)
              <:
              Core.Ops.Range.t_Range usize)
            result
            (fun result j ->
                let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
                  result
                in
            assume (range (Rust_primitives.Integers.v #i32_inttype ((result.[i]).Libcrux.Kem.Kyber.Arithmetic.f_coefficients.[j]) * 1441) i32_inttype);
            assume (Libcrux.Kem.Kyber.Arithmetic.montgomery_pre ((result.[i]).Libcrux.Kem.Kyber.Arithmetic.f_coefficients.[j] *! 1441l));
                let j:usize = j in
                let coefficient_normal_form:i32 =
                  Libcrux.Kem.Kyber.Arithmetic.montgomery_reduce (((result.[ i ]
                          <:
                          Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                          .Libcrux.Kem.Kyber.Arithmetic.f_coefficients.[ j ]
                        <:
                        i32) *!
                      1441l
                      <:
                      i32)
                in
          assume (range (v coefficient_normal_form +
                        v #i32_inttype (error_1_.[i]).Libcrux.Kem.Kyber.Arithmetic.f_coefficients.[ j ])
                        i32_inttype);
          assume (Libcrux.Kem.Kyber.Arithmetic.barrett_pre (coefficient_normal_form +! (error_1_.[i]).Libcrux.Kem.Kyber.Arithmetic.f_coefficients.[ j ]));
                let result:t_Array Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement v_K =
                  Rust_primitives.Hax.Monomorphized_update_at.update_at_usize result
                    i
                    ({
                        (result.[ i ] <: Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement) with
                        Libcrux.Kem.Kyber.Arithmetic.f_coefficients
                        =
                        Rust_primitives.Hax.Monomorphized_update_at.update_at_usize (result.[ i ]
                            <:
                            Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                            .Libcrux.Kem.Kyber.Arithmetic.f_coefficients
                          j
                          (Libcrux.Kem.Kyber.Arithmetic.barrett_reduce (coefficient_normal_form +!
                                ((error_1_.[ i ]
                                    <:
                                    Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                                    .Libcrux.Kem.Kyber.Arithmetic.f_coefficients.[ j ]
                                  <:
                                  i32)
                                <:
                                i32)
                            <:
                            i32)
                        <:
                        t_Array i32 (sz 256)
                      }
                      <:
                      Libcrux.Kem.Kyber.Arithmetic.t_PolynomialRingElement)
                in
                result))
  in
  result
