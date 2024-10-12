#ifndef I_DDCBENUMS_HPP
#define I_DDCBENUMS_HPP

namespace Trpp::CPU{

enum class DDCBenums{
  undefined,

  // Rotate Shift Group
  RLC_ixd,
  RL_ixd,
  RRC_ixd,
  RR_ixd,
  SLA_ixd,
  SRA_ixd,
  SRL_ixd,

  // Bit Set Group
  BIT_b_ixd,
  SET_b_ixd,
  RES_b_ixd,
};

}

#endif
