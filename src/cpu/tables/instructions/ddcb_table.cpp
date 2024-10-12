#include "ddcb_table.hpp"

namespace Trpp::CPU::Instructions{

//-------------------------------------------------------------
// lifetime
//-------------------------------------------------------------

DDCBTable::DDCBTable(): m_buffer{}{
  m_buffer.fill(DDCBenums::undefined);
  SetEntries();
}

//-------------------------------------------------------------
// Operational
//-------------------------------------------------------------

void DDCBTable::SetEntries() noexcept{
  using enum DDCBenums;


  ////////////////////////////////////////////////
  // Rotate shift group
  ////////////////////////////////////////////////

  // RLC ix+d
  m_buffer[0x06] = DDCBenums::RLC_ixd;
  
  // RL ix+d
  m_buffer[0x16] = DDCBenums::RL_ixd;
  
  // RRC ix+d
  m_buffer[0x0e] = DDCBenums::RRC_ixd;

  // RR ix+d
  m_buffer[0x1e] = DDCBenums::RR_ixd;

  // SLA ix+d
  m_buffer[0x26] = DDCBenums::SLA_ixd;

  // SRA ix+d
  m_buffer[0x2e] = DDCBenums::SRA_ixd;

  // SRL ix+d
  m_buffer[0x3e] = DDCBenums::SRL_ixd;

  ////////////////////////////////////////////////
  // Bit Set Group
  ////////////////////////////////////////////////

  // BIT b, ix+d
  m_buffer[0x46] = DDCBenums::BIT_b_ixd;
  m_buffer[0x4e] = DDCBenums::BIT_b_ixd;
  m_buffer[0x56] = DDCBenums::BIT_b_ixd;
  m_buffer[0x5e] = DDCBenums::BIT_b_ixd;
  m_buffer[0x66] = DDCBenums::BIT_b_ixd;
  m_buffer[0x6e] = DDCBenums::BIT_b_ixd;
  m_buffer[0x76] = DDCBenums::BIT_b_ixd;
  m_buffer[0x7e] = DDCBenums::BIT_b_ixd;

  // SET b, ix+d
  m_buffer[0xc6] = DDCBenums::SET_b_ixd;
  m_buffer[0xce] = DDCBenums::SET_b_ixd;
  m_buffer[0xd6] = DDCBenums::SET_b_ixd;
  m_buffer[0xde] = DDCBenums::SET_b_ixd;
  m_buffer[0xe6] = DDCBenums::SET_b_ixd;
  m_buffer[0xee] = DDCBenums::SET_b_ixd;
  m_buffer[0xf6] = DDCBenums::SET_b_ixd;
  m_buffer[0xfe] = DDCBenums::SET_b_ixd;
  
  // RES b, ix+d
  m_buffer[0x86] = DDCBenums::RES_b_ixd;
  m_buffer[0x8e] = DDCBenums::RES_b_ixd;
  m_buffer[0x96] = DDCBenums::RES_b_ixd;
  m_buffer[0x9e] = DDCBenums::RES_b_ixd;
  m_buffer[0xa6] = DDCBenums::RES_b_ixd;
  m_buffer[0xae] = DDCBenums::RES_b_ixd;
  m_buffer[0xb6] = DDCBenums::RES_b_ixd;
  m_buffer[0xbe] = DDCBenums::RES_b_ixd;
}

//-------------------------------------------------------------
// Operator overloads
//-------------------------------------------------------------

[[nodiscard]] DDCBenums 
DDCBTable::operator[](std::size_t index) const { 
  assert(index < TABLE_SIZE);
  return m_buffer[index];
}

} 
