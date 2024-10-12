#include "dd_table.hpp"

namespace Trpp::CPU::Instructions{

//-------------------------------------------------------------
// lifetime
//-------------------------------------------------------------

DDTable::DDTable(): m_buffer{}{
  m_buffer.fill(DDenums::undefined);
  SetEntries();
}

//-------------------------------------------------------------
// Operational
//-------------------------------------------------------------

void DDTable::SetEntries() noexcept{
  using enum DDenums;

  ////////////////////////////////////////////////
  // 8-bit Load Group
  ////////////////////////////////////////////////

  // LD r, (ix + d)
  m_buffer[0x46] = DDenums::LD_r_ixd;
  m_buffer[0x4e] = DDenums::LD_r_ixd;
  m_buffer[0x56] = DDenums::LD_r_ixd;
  m_buffer[0x5e] = DDenums::LD_r_ixd;
  m_buffer[0x66] = DDenums::LD_r_ixd;
  m_buffer[0x6e] = DDenums::LD_r_ixd;
  m_buffer[0x7e] = DDenums::LD_r_ixd;

  // LD (ix + d), r
  m_buffer[0x70] = DDenums::LD_ixd_r;
  m_buffer[0x71] = DDenums::LD_ixd_r;
  m_buffer[0x72] = DDenums::LD_ixd_r;
  m_buffer[0x73] = DDenums::LD_ixd_r;
  m_buffer[0x74] = DDenums::LD_ixd_r;
  m_buffer[0x75] = DDenums::LD_ixd_r;
  m_buffer[0x77] = DDenums::LD_ixd_r;

  // LD (ix + d), n
  m_buffer[0x36] = DDenums::LD_ixd_n;

  ////////////////////////////////////////////////
  // 16-bit Load Group
  ////////////////////////////////////////////////

  // LD ix, nn
  m_buffer[0x21] = DDenums::LD_ix_nn;

  // LD ix, (nn)
  m_buffer[0x2a] = DDenums::LD_ix_nn_indirect;

  // LD (nn) ix
  m_buffer[0x22] = DDenums::LD_nn_ix_indirect;

  // LD sp, ix
  m_buffer[0xf9] = DDenums::LD_sp_ix;

  // Push IX
  m_buffer[0xe5] = DDenums::PUSH_ix;

  // Pop ix
  m_buffer[0xe1] = DDenums::POP_ix;

  ////////////////////////////////////////////////
  // Exchange Group
  ////////////////////////////////////////////////

  // Ex sp ix
  m_buffer[0xe3] = DDenums::EX_sp_ix;

  ////////////////////////////////////////////////
  // 8-bit Arithmetic Group
  ////////////////////////////////////////////////

  // ADD a, ix+d
  m_buffer[0x86] = DDenums::ADD_a_ixd;

  // ADC a, ix + d
  m_buffer[0x8e] = DDenums::ADC_a_ixd;

  // SUB a, ix + d
  m_buffer[0x96] = DDenums::SUB_a_ixd;

  // SBC a, ix + d
  m_buffer[0x9e] = DDenums::SBC_a_ixd;

  // AND a, ix + d
  m_buffer[0xa6] = DDenums::AND_a_ixd;

  // OR a, ix + d
  m_buffer[0xb6] = DDenums::OR_a_ixd;

  // XOR a, ix + d
  m_buffer[0xae] = DDenums::XOR_a_ixd;

  // CP a, ix + d
  m_buffer[0xbe] = DDenums::CP_a_ixd;

  // INC ix + d
  m_buffer[0x34] = DDenums::INC_ixd;

  // DEC ix + d
  m_buffer[0x35] = DDenums::DEC_ixd;

  ////////////////////////////////////////////////
  // 16-bit Arithmetic Group
  ////////////////////////////////////////////////

  // Add ix pp
  m_buffer[0x09] = DDenums::ADD_ix_pp;
  m_buffer[0x19] = DDenums::ADD_ix_pp;
  m_buffer[0x29] = DDenums::ADD_ix_pp;
  m_buffer[0x39] = DDenums::ADD_ix_pp;

  // INC ix
  m_buffer[0x23] = DDenums::INC_ix;

  // DEC ix
  m_buffer[0x2b] = DDenums::DEC_ix;

  ////////////////////////////////////////////////
  // Rotate and Shift Group
  ////////////////////////////////////////////////

}

//-------------------------------------------------------------
// Operator overloads
//-------------------------------------------------------------

[[nodiscard]] DDenums 
DDTable::operator[](std::size_t index) const { 
  assert(index < TABLE_SIZE);
  return m_buffer[index];
}

} 

