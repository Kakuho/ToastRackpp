#ifndef I_ENUMS_HPP
#define I_ENUMS_HPP

// Enums for Instructions with DD Prefix, 
// also includes DDCB prefixed.
//
// Reference: Zilog Z80 Reference

namespace Trpp::CPU{

enum class DDenums{
  undefined,

  // 8-bit loads
  LD_r_ixd,
  LD_ixd_r,
  LD_ixd_n,

  // 16-bit loads
  LD_ix_nn,
  LD_ix_nn_indirect,
  LD_nn_ix_indirect,
  LD_sp_ix,
  PUSH_ix,
  POP_ix,

  // Exchange group
  EX_sp_ix,
  
  // 8-bit aithmetic
  ADD_a_ixd,
  ADC_a_ixd,
  SUB_a_ixd,
  SBC_a_ixd,
  AND_a_ixd,
  OR_a_ixd,
  XOR_a_ixd,
  CP_a_ixd,
  INC_ixd,
  DEC_ixd,

  // 16-bit arithmetic
  ADD_ix_pp,
  INC_ix,
  DEC_ix,

  // Rotate Shift Group
  RLC_ixd,
  RL_ixd,
  RRC_ixd,
  RR_ixd,
  SLA_ixd,
  SRA_ixd,
  SRL_ixd,

  // bit set group
  BIT_b_ixd,
  SET_b_ixd,
  RES_b_ixd,

  // Jump group
  JP_ix,
};


} // namespace trpp::instructions

#endif
