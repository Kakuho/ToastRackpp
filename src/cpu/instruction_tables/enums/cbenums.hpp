#ifndef I_CB_ENUMS_HPP
#define I_CB_ENUMS_HPP

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

enum class CBenums{
  undefined,
};

} // namespace trpp::instructions

#endif
