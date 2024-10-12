#include "fdcb_table.hpp"

namespace Trpp::CPU::Instructions{

//-------------------------------------------------------------
// lifetime
//-------------------------------------------------------------

FDCBTable::FDCBTable(): m_buffer{}{
  m_buffer.fill(FDCBenums::undefined);
  SetEntries();
}

//-------------------------------------------------------------
// Operational
//-------------------------------------------------------------

void FDCBTable::SetEntries() noexcept{
  using enum FDCBenums;


  ////////////////////////////////////////////////
  // Rotate shift group
  ////////////////////////////////////////////////

  // RLC iy+d
  m_buffer[0x06] = FDCBenums::RLC_iyd;
  
  // RL iy+d
  m_buffer[0x16] = FDCBenums::RL_iyd;
  
  // RRC iy+d
  m_buffer[0x0e] = FDCBenums::RRC_iyd;

  // RR iy+d
  m_buffer[0x1e] = FDCBenums::RR_iyd;

  // SLA iy+d
  m_buffer[0x26] = FDCBenums::SLA_iyd;

  // SRA iy+d
  m_buffer[0x2e] = FDCBenums::SRA_iyd;

  // SRL iy+d
  m_buffer[0x3e] = FDCBenums::SRL_iyd;

  ////////////////////////////////////////////////
  // Bit Set Group
  ////////////////////////////////////////////////

  // BIT b, iy+d
  m_buffer[0x46] = FDCBenums::BIT_b_iyd;
  m_buffer[0x4e] = FDCBenums::BIT_b_iyd;
  m_buffer[0x56] = FDCBenums::BIT_b_iyd;
  m_buffer[0x5e] = FDCBenums::BIT_b_iyd;
  m_buffer[0x66] = FDCBenums::BIT_b_iyd;
  m_buffer[0x6e] = FDCBenums::BIT_b_iyd;
  m_buffer[0x76] = FDCBenums::BIT_b_iyd;
  m_buffer[0x7e] = FDCBenums::BIT_b_iyd;

  // SET b, iy+d
  m_buffer[0xc6] = FDCBenums::SET_b_iyd;
  m_buffer[0xce] = FDCBenums::SET_b_iyd;
  m_buffer[0xd6] = FDCBenums::SET_b_iyd;
  m_buffer[0xde] = FDCBenums::SET_b_iyd;
  m_buffer[0xe6] = FDCBenums::SET_b_iyd;
  m_buffer[0xee] = FDCBenums::SET_b_iyd;
  m_buffer[0xf6] = FDCBenums::SET_b_iyd;
  m_buffer[0xfe] = FDCBenums::SET_b_iyd;
  
  // RES b, iy+d
  m_buffer[0x86] = FDCBenums::RES_b_iyd;
  m_buffer[0x8e] = FDCBenums::RES_b_iyd;
  m_buffer[0x96] = FDCBenums::RES_b_iyd;
  m_buffer[0x9e] = FDCBenums::RES_b_iyd;
  m_buffer[0xa6] = FDCBenums::RES_b_iyd;
  m_buffer[0xae] = FDCBenums::RES_b_iyd;
  m_buffer[0xb6] = FDCBenums::RES_b_iyd;
  m_buffer[0xbe] = FDCBenums::RES_b_iyd;
}

//-------------------------------------------------------------
// Operator overloads
//-------------------------------------------------------------

[[nodiscard]] FDCBenums 
FDCBTable::operator[](std::size_t index) const { 
  assert(index < TABLE_SIZE);
  return m_buffer[index];
}

} 
