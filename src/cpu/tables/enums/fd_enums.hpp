#ifndef I_FDENUMS_HPP
#define I_FDENUMS_HPP

// Enums for Instructions with FD Prefix, 
// also includes FDCB prefixed.
//
// Reference: Zilog Z80 Reference

namespace Trpp::CPU{

enum class FDenums{
  undefined,

  // 8-bit loads
  LD_r_iyd,
  LD_iyd_r,
  LD_iyd_n,

  // 16-bit loads
  LD_iy_nn,
  LD_iy_nn_indirect,
  LD_nn_iy_indirect,
  LD_sp_iy,
  PUSH_iy,
  POP_iy,

  // Exchange group
  EX_sp_iy,
  
  // 8-bit aithmetic
  ADD_a_iyd,
  ADC_a_iyd,
  SUB_a_iyd,
  SBC_a_iyd,
  AND_a_iyd,
  OR_a_iyd,
  XOR_a_iyd,
  CP_a_iyd,
  INC_iyd,
  DEC_iyd,

  // 16-bit arithmetic
  ADD_iy_rr,
  INC_iy,
  DEC_iy,

  // Jump group
  JP_iy,
};


} // namespace trpp::instructions

#endif
