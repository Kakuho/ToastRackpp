#include "cb_table.hpp"

namespace Trpp::CPU::Instructions{

//-------------------------------------------------------------
// lifetime
//-------------------------------------------------------------

CBTable::CBTable(): m_buffer{}{
  m_buffer.fill(CBenums::undefined);
  SetEntries();
}

//-------------------------------------------------------------
// Operational
//-------------------------------------------------------------

void CBTable::SetEntries() noexcept{
  using enum CBenums;

  ////////////////////////////////////////////////
  // Rotation Group
  ////////////////////////////////////////////////

  // RLC_r
  m_buffer[0x07] = CBenums::RLC_r;
  m_buffer[0x00] = CBenums::RLC_r;
  m_buffer[0x01] = CBenums::RLC_r;
  m_buffer[0x02] = CBenums::RLC_r;
  m_buffer[0x03] = CBenums::RLC_r;
  m_buffer[0x04] = CBenums::RLC_r;
  m_buffer[0x05] = CBenums::RLC_r;

  // RLC_hl
  m_buffer[0x06] = CBenums::RLC_hl;

  // RL_r
  m_buffer[0x17] = CBenums::RL_r;
  m_buffer[0x10] = CBenums::RL_r;
  m_buffer[0x11] = CBenums::RL_r;
  m_buffer[0x12] = CBenums::RL_r;
  m_buffer[0x13] = CBenums::RL_r;
  m_buffer[0x14] = CBenums::RL_r;
  m_buffer[0x15] = CBenums::RL_r;

  // RL_hl
  m_buffer[0x16] = CBenums::RL_hl;

  // RRC_r
  m_buffer[0x0f] = CBenums::RRC_r;
  m_buffer[0x08] = CBenums::RRC_r;
  m_buffer[0x09] = CBenums::RRC_r;
  m_buffer[0x0a] = CBenums::RRC_r;
  m_buffer[0x0b] = CBenums::RRC_r;
  m_buffer[0x0c] = CBenums::RRC_r;
  m_buffer[0x0d] = CBenums::RRC_r;

  // RRC_hl
  m_buffer[0x0e] = CBenums::RRC_hl;

  // SLA_r
  m_buffer[0x27] = CBenums::SLA_r;
  m_buffer[0x20] = CBenums::SLA_r;
  m_buffer[0x21] = CBenums::SLA_r;
  m_buffer[0x22] = CBenums::SLA_r;
  m_buffer[0x23] = CBenums::SLA_r;
  m_buffer[0x24] = CBenums::SLA_r;
  m_buffer[0x25] = CBenums::SLA_r;

  // SLA_hl
  m_buffer[0x26] = CBenums::SLA_hl;

  // SRA_r
  m_buffer[0x2f] = CBenums::SRA_r;
  m_buffer[0x28] = CBenums::SRA_r;
  m_buffer[0x29] = CBenums::SRA_r;
  m_buffer[0x2a] = CBenums::SRA_r;
  m_buffer[0x2b] = CBenums::SRA_r;
  m_buffer[0x2c] = CBenums::SRA_r;
  m_buffer[0x2d] = CBenums::SRA_r;

  // SRA_hl
  m_buffer[0x2e] = CBenums::SRA_hl;

  // SRL_r
  m_buffer[0x3f] = CBenums::SRL_r;
  m_buffer[0x38] = CBenums::SRL_r;
  m_buffer[0x39] = CBenums::SRL_r;
  m_buffer[0x3a] = CBenums::SRL_r;
  m_buffer[0x3b] = CBenums::SRL_r;
  m_buffer[0x3c] = CBenums::SRL_r;
  m_buffer[0x3d] = CBenums::SRL_r;

  // SRL_hl
  m_buffer[0x3e] = CBenums::SRL_hl;

  ////////////////////////////////////////////////
  // Bit Set Reset Group
  ////////////////////////////////////////////////

  // BIT_b_r
  m_buffer[0x47] = CBenums::BIT_b_r;
  m_buffer[0x40] = CBenums::BIT_b_r;
  m_buffer[0x41] = CBenums::BIT_b_r;
  m_buffer[0x42] = CBenums::BIT_b_r;
  m_buffer[0x43] = CBenums::BIT_b_r;
  m_buffer[0x44] = CBenums::BIT_b_r;
  m_buffer[0x45] = CBenums::BIT_b_r;
  m_buffer[0x4f] = CBenums::BIT_b_r;
  m_buffer[0x48] = CBenums::BIT_b_r;
  m_buffer[0x49] = CBenums::BIT_b_r;
  m_buffer[0x4a] = CBenums::BIT_b_r;
  m_buffer[0x4b] = CBenums::BIT_b_r;
  m_buffer[0x4c] = CBenums::BIT_b_r;
  m_buffer[0x4d] = CBenums::BIT_b_r;
  m_buffer[0x57] = CBenums::BIT_b_r;
  m_buffer[0x50] = CBenums::BIT_b_r;
  m_buffer[0x51] = CBenums::BIT_b_r;
  m_buffer[0x52] = CBenums::BIT_b_r;
  m_buffer[0x53] = CBenums::BIT_b_r;
  m_buffer[0x54] = CBenums::BIT_b_r;
  m_buffer[0x55] = CBenums::BIT_b_r;
  m_buffer[0x5f] = CBenums::BIT_b_r;
  m_buffer[0x58] = CBenums::BIT_b_r;
  m_buffer[0x59] = CBenums::BIT_b_r;
  m_buffer[0x5a] = CBenums::BIT_b_r;
  m_buffer[0x5b] = CBenums::BIT_b_r;
  m_buffer[0x5c] = CBenums::BIT_b_r;
  m_buffer[0x5d] = CBenums::BIT_b_r;
  m_buffer[0x67] = CBenums::BIT_b_r;
  m_buffer[0x60] = CBenums::BIT_b_r;
  m_buffer[0x61] = CBenums::BIT_b_r;
  m_buffer[0x62] = CBenums::BIT_b_r;
  m_buffer[0x63] = CBenums::BIT_b_r;
  m_buffer[0x64] = CBenums::BIT_b_r;
  m_buffer[0x65] = CBenums::BIT_b_r;
  m_buffer[0x6f] = CBenums::BIT_b_r;
  m_buffer[0x68] = CBenums::BIT_b_r;
  m_buffer[0x69] = CBenums::BIT_b_r;
  m_buffer[0x6a] = CBenums::BIT_b_r;
  m_buffer[0x6b] = CBenums::BIT_b_r;
  m_buffer[0x6c] = CBenums::BIT_b_r;
  m_buffer[0x6d] = CBenums::BIT_b_r;
  m_buffer[0x77] = CBenums::BIT_b_r;
  m_buffer[0x70] = CBenums::BIT_b_r;
  m_buffer[0x71] = CBenums::BIT_b_r;
  m_buffer[0x72] = CBenums::BIT_b_r;
  m_buffer[0x73] = CBenums::BIT_b_r;
  m_buffer[0x74] = CBenums::BIT_b_r;
  m_buffer[0x75] = CBenums::BIT_b_r;
  m_buffer[0x7f] = CBenums::BIT_b_r;
  m_buffer[0x78] = CBenums::BIT_b_r;
  m_buffer[0x79] = CBenums::BIT_b_r;
  m_buffer[0x7a] = CBenums::BIT_b_r;
  m_buffer[0x7b] = CBenums::BIT_b_r;
  m_buffer[0x7c] = CBenums::BIT_b_r;
  m_buffer[0x7d] = CBenums::BIT_b_r;

  // BIT b , hl
  m_buffer[0x46] = CBenums::BIT_b_hl;
  m_buffer[0x4e] = CBenums::BIT_b_hl;
  m_buffer[0x56] = CBenums::BIT_b_hl;
  m_buffer[0x5e] = CBenums::BIT_b_hl;
  m_buffer[0x66] = CBenums::BIT_b_hl;
  m_buffer[0x6e] = CBenums::BIT_b_hl;
  m_buffer[0x76] = CBenums::BIT_b_hl;
  m_buffer[0x7e] = CBenums::BIT_b_hl;

  // SET b, r
  m_buffer[0xc0] = CBenums::SET_b_r;
  m_buffer[0xc1] = CBenums::SET_b_r;
  m_buffer[0xc2] = CBenums::SET_b_r;
  m_buffer[0xc3] = CBenums::SET_b_r;
  m_buffer[0xc4] = CBenums::SET_b_r;
  m_buffer[0xc5] = CBenums::SET_b_r;
  m_buffer[0xc7] = CBenums::SET_b_r;
  m_buffer[0xc8] = CBenums::SET_b_r;
  m_buffer[0xc9] = CBenums::SET_b_r;
  m_buffer[0xca] = CBenums::SET_b_r;
  m_buffer[0xcb] = CBenums::SET_b_r;
  m_buffer[0xcc] = CBenums::SET_b_r;
  m_buffer[0xcd] = CBenums::SET_b_r;
  m_buffer[0xcf] = CBenums::SET_b_r;
  m_buffer[0xd0] = CBenums::SET_b_r;
  m_buffer[0xd1] = CBenums::SET_b_r;
  m_buffer[0xd2] = CBenums::SET_b_r;
  m_buffer[0xd3] = CBenums::SET_b_r;
  m_buffer[0xd4] = CBenums::SET_b_r;
  m_buffer[0xd5] = CBenums::SET_b_r;
  m_buffer[0xd7] = CBenums::SET_b_r;
  m_buffer[0xd8] = CBenums::SET_b_r;
  m_buffer[0xd9] = CBenums::SET_b_r;
  m_buffer[0xda] = CBenums::SET_b_r;
  m_buffer[0xdb] = CBenums::SET_b_r;
  m_buffer[0xdc] = CBenums::SET_b_r;
  m_buffer[0xdd] = CBenums::SET_b_r;
  m_buffer[0xdf] = CBenums::SET_b_r;
  m_buffer[0xe0] = CBenums::SET_b_r;
  m_buffer[0xe1] = CBenums::SET_b_r;
  m_buffer[0xe2] = CBenums::SET_b_r;
  m_buffer[0xe3] = CBenums::SET_b_r;
  m_buffer[0xe4] = CBenums::SET_b_r;
  m_buffer[0xe5] = CBenums::SET_b_r;
  m_buffer[0xe7] = CBenums::SET_b_r;
  m_buffer[0xe8] = CBenums::SET_b_r;
  m_buffer[0xe9] = CBenums::SET_b_r;
  m_buffer[0xea] = CBenums::SET_b_r;
  m_buffer[0xeb] = CBenums::SET_b_r;
  m_buffer[0xec] = CBenums::SET_b_r;
  m_buffer[0xed] = CBenums::SET_b_r;
  m_buffer[0xef] = CBenums::SET_b_r;
  m_buffer[0xf0] = CBenums::SET_b_r;
  m_buffer[0xf1] = CBenums::SET_b_r;
  m_buffer[0xf2] = CBenums::SET_b_r;
  m_buffer[0xf3] = CBenums::SET_b_r;
  m_buffer[0xf4] = CBenums::SET_b_r;
  m_buffer[0xf5] = CBenums::SET_b_r;
  m_buffer[0xf7] = CBenums::SET_b_r;
  m_buffer[0xf8] = CBenums::SET_b_r;
  m_buffer[0xf9] = CBenums::SET_b_r;
  m_buffer[0xfa] = CBenums::SET_b_r;
  m_buffer[0xfb] = CBenums::SET_b_r;
  m_buffer[0xfc] = CBenums::SET_b_r;
  m_buffer[0xfd] = CBenums::SET_b_r;
  m_buffer[0xff] = CBenums::SET_b_r;

  // SET_b_hl
  m_buffer[0xc6] = CBenums::SET_b_hl;
  m_buffer[0xce] = CBenums::SET_b_hl;
  m_buffer[0xd6] = CBenums::SET_b_hl;
  m_buffer[0xde] = CBenums::SET_b_hl;
  m_buffer[0xe6] = CBenums::SET_b_hl;
  m_buffer[0xee] = CBenums::SET_b_hl;
  m_buffer[0xf6] = CBenums::SET_b_hl;
  m_buffer[0xfe] = CBenums::SET_b_hl;

  // RES_b_m
  m_buffer[0x80] = CBenums::RES_b_r;
  m_buffer[0x81] = CBenums::RES_b_r;
  m_buffer[0x82] = CBenums::RES_b_r;
  m_buffer[0x83] = CBenums::RES_b_r;
  m_buffer[0x84] = CBenums::RES_b_r;
  m_buffer[0x85] = CBenums::RES_b_r;
  m_buffer[0x87] = CBenums::RES_b_r;
  m_buffer[0x88] = CBenums::RES_b_r;
  m_buffer[0x89] = CBenums::RES_b_r;
  m_buffer[0x8a] = CBenums::RES_b_r;
  m_buffer[0x8b] = CBenums::RES_b_r;
  m_buffer[0x8c] = CBenums::RES_b_r;
  m_buffer[0x8d] = CBenums::RES_b_r;
  m_buffer[0x8f] = CBenums::RES_b_r;
  m_buffer[0x90] = CBenums::RES_b_r;
  m_buffer[0x91] = CBenums::RES_b_r;
  m_buffer[0x92] = CBenums::RES_b_r;
  m_buffer[0x93] = CBenums::RES_b_r;
  m_buffer[0x94] = CBenums::RES_b_r;
  m_buffer[0x95] = CBenums::RES_b_r;
  m_buffer[0x97] = CBenums::RES_b_r;
  m_buffer[0x98] = CBenums::RES_b_r;
  m_buffer[0x99] = CBenums::RES_b_r;
  m_buffer[0x9a] = CBenums::RES_b_r;
  m_buffer[0x9b] = CBenums::RES_b_r;
  m_buffer[0x9c] = CBenums::RES_b_r;
  m_buffer[0x9d] = CBenums::RES_b_r;
  m_buffer[0x9f] = CBenums::RES_b_r;
  m_buffer[0xa0] = CBenums::RES_b_r;
  m_buffer[0xa1] = CBenums::RES_b_r;
  m_buffer[0xa2] = CBenums::RES_b_r;
  m_buffer[0xa3] = CBenums::RES_b_r;
  m_buffer[0xa4] = CBenums::RES_b_r;
  m_buffer[0xa5] = CBenums::RES_b_r;
  m_buffer[0xa7] = CBenums::RES_b_r;
  m_buffer[0xa8] = CBenums::RES_b_r;
  m_buffer[0xa9] = CBenums::RES_b_r;
  m_buffer[0xaa] = CBenums::RES_b_r;
  m_buffer[0xab] = CBenums::RES_b_r;
  m_buffer[0xac] = CBenums::RES_b_r;
  m_buffer[0xad] = CBenums::RES_b_r;
  m_buffer[0xaf] = CBenums::RES_b_r;
  m_buffer[0xb0] = CBenums::RES_b_r;
  m_buffer[0xb1] = CBenums::RES_b_r;
  m_buffer[0xb2] = CBenums::RES_b_r;
  m_buffer[0xb3] = CBenums::RES_b_r;
  m_buffer[0xb4] = CBenums::RES_b_r;
  m_buffer[0xb5] = CBenums::RES_b_r;
  m_buffer[0xb7] = CBenums::RES_b_r;
  m_buffer[0xb8] = CBenums::RES_b_r;
  m_buffer[0xb9] = CBenums::RES_b_r;
  m_buffer[0xba] = CBenums::RES_b_r;
  m_buffer[0xbb] = CBenums::RES_b_r;
  m_buffer[0xbc] = CBenums::RES_b_r;
  m_buffer[0xbd] = CBenums::RES_b_r;
  m_buffer[0xbf] = CBenums::RES_b_r;
  
  // RES_b_hl
  m_buffer[0x86] = CBenums::RES_b_hl;
  m_buffer[0x8e] = CBenums::RES_b_hl;
  m_buffer[0x96] = CBenums::RES_b_hl;
  m_buffer[0x9e] = CBenums::RES_b_hl;
  m_buffer[0xa6] = CBenums::RES_b_hl;
  m_buffer[0xae] = CBenums::RES_b_hl;
  m_buffer[0xb6] = CBenums::RES_b_hl;
  m_buffer[0xbe] = CBenums::RES_b_hl;
}

//-------------------------------------------------------------
// Operator overloads
//-------------------------------------------------------------

[[nodiscard]] CBenums 
CBTable::operator[](std::size_t index) const { 
  assert(index < TABLE_SIZE);
  return m_buffer[index];
}

} 

