#ifndef I_FDCBENUMS_HPP
#define I_FDCBENUMS_HPP

// Enums for Instructions with FD Prefix, 
// also includes FDCB prefixed.
//
// Reference: Zilog Z80 Reference

namespace Trpp::CPU{

enum class FDCBenums{
  undefined,

  // Rotate Shift Group
  RLC_iyd,
  RL_iyd,
  RRC_iyd,
  RR_iyd,
  SLA_iyd,
  SRA_iyd,
  SRL_iyd,

  // Bit Set Group
  BIT_b_iyd,
  SET_b_iyd,
  RES_b_iyd,
};

}

#endif
