#ifndef I_ENUMS_HPP
#define I_ENUMS_HPP

// Enums for Instructions with no Prefix
//
// Reference: 
//
// NOTATION:
//
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

enum class EDenums{
  undefined,

  // 8-bit loads
  LD_a_i,
  LD_a_r,
  LD_i_a,
  LD_r_a,

  // 16-bit loads
  LD_dd_nn,
  LD_nn_dd,

  // Exchange group
  LDI,
  LDIR,

  LDD,
  LDDR,

  CPI,
  CPIR,

  CPD,
  CPDR,

  // General group
  NEG,
  IM0,
  IM1,
  IM2,

  // 16-bit arithmetic
  ADC_hl_ss,
  SBC_hl_ss,

  // Rotate Shift Group
  RLD,
  RRD,

  // Call Return Group
  RETI,
  RETN,

  // Input Output Group
  IN_r_c,
  INI,
  INIR,
  IND,
  INDR,
  OUT_c_r,
  OUTI,
  OTIR,
  OUTD,
  OTDR,
};

} // namespace trpp::instructions

#endif
