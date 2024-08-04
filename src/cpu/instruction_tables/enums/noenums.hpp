#ifndef I_ENUMS_HPP
#define I_ENUMS_HPP

// NOTATION:
// r - 8-bit reg A, B, C, D, E, H, or L
// n - 1 byte unsigned 
// nn - 2 byte unsigned
// d - 1 byte signed
// b - 1 bit expression
// e - 1 byte signed 
// cc -  (NZ, Z, NC, C, PO, PE, P, or M),
// qq - register pairs BC, DE, HL or AF
// ss - register pairs BC, DE, HL or SP
// pp - register pairs BC, DE, IX or SP
// rr - register pairs BC, DE, IY or SP
// s  - r, n, (HL), (IX+d) or (IY+d)
// m  - r, (HL), (IX+d) or (IY+d)
//
// my own notation
//
// dd - BC DE HL SP

namespace trpp::instructions{

enum class noprefix_enums{
  Undefined,

  // 8 bit Loads
  LD_r_r,
  LD_r_n,
  LD_r_hl,
  LD_hl_r,   
  LD_hl_n,
  LD_a_bc,
  LD_a_de,
  LD_a_nn,
  LD_bc_a,
  LD_de_a,
  LD_nn_a,

  // 16-bit Loads
  LD_dd_nn,
  LD_hl_nn,
  LD_nn_hl,
  LD_sp_hl,
  Push_qq,
  Pop_qq,

  // Exchange
  EX_de_hl,
  EX_AF_AF2,
  EXX,
  EX_sp_hl,

  // 8-bit alu
  ADD_a_r,
  ADD_a_n,
  ADD_a_hl,
  ADC_a_r,
  ADC_a_n,
  ADC_a_hl,
  SUB_a_r,
  SUB_a_n,
  SUB_a_hl,
  SBC_a_r,
  SBC_a_n,
  SBC_a_hl,
    /* TODO: ANDS */
    /* TODO: ORS */
  XOR_a_r,
  XOR_a_n,
  XOR_a_hl,
    /* TODO: CPs */
  INC_r,
  INC_hl,
  DEC_r,
  DEC_hl,

  // General
  DAA,
  CPL,
  CCF,
  SCF,
  NOP,
  HALT,
  DI,
  EI,

  // Rotates
  // TODO

  // Jumps
  JP_nn,
  JP_cc_nn,
  JR_e,
  JR_c_e,
  JR_nc_e,
  JR_z_e,
  JR_nz_e,
  DJNZ_e,

  // Call Return
  CALL_nn,
  CALL_cc_nn,
  RET,
  RET_cc,
  RST         

  // IO group
  // TODO

};

} // namespace trpp::instructions

#endif
