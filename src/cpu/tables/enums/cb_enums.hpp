#ifndef I_CB_ENUMS_HPP
#define I_CB_ENUMS_HPP

// Enums for instructions prefixed with byte CB
//
// Reference:
//
// NOTATION:
//    r - 8-bit reg A, B, C, D, E, H, or L
//    n - 1 byte unsigned 
//    nn - 2 byte unsigned
//    d - 1 byte signed
//    b - 1 bit expression
//    e - 1 byte signed 
//    cc -  (NZ, Z, NC, C, PO, PE, P, or M),
//    qq - register pairs BC, DE, HL or AF
//    ss - register pairs BC, DE, HL or SP
//    pp - register pairs BC, DE, IX or SP
//    rr - register pairs BC, DE, IY or SP
//    s  - r, n, (HL), (IX+d) or (IY+d)
//    m  - r, (HL), (IX+d) or (IY+d)
//
// my own notation
//
//    dd - BC DE HL SP

namespace Trpp::CPU{

enum class CBenums{
  undefined,

  // rotate group

  RLC_r,
  RLC_hl,

  RL_r,
  RL_hl,

  RRC_r,
  RRC_hl,

  RR_r,
  RR_hl,

  SLA_r,
  SLA_hl,

  SRA_r,
  SRA_hl,

  SRL_r,
  SRL_hl,
  
  // bit set group

  BIT_b_r,
  BIT_b_hl,

  SET_b_r,
  SET_b_hl,

  RES_b_r,
  RES_b_hl,

};

} // namespace trpp::instructions

#endif
