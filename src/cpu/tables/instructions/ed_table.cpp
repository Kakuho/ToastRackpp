#include "ed_table.hpp"

namespace Trpp::CPU::Instructions{

//-------------------------------------------------------------
// lifetime
//-------------------------------------------------------------

EDTable::EDTable(): m_buffer{}{
  m_buffer.fill(EDenums::undefined);
  SetEntries();
}

//-------------------------------------------------------------
// Operational
//-------------------------------------------------------------

void EDTable::SetEntries() noexcept{
  using enum EDenums;

  ////////////////////////////////////////////////
  // 8-bit load Group
  ////////////////////////////////////////////////

  // LD_a_i
  m_buffer[0x57] = EDenums::LD_a_i;

  // LD_a_r
  m_buffer[0x5f] = EDenums::LD_a_r;

  // LD_i_a
  m_buffer[0x47] = EDenums::LD_i_a;

  // LD_r_a
  m_buffer[0x4f] = EDenums::LD_r_a;

  ////////////////////////////////////////////////
  // 16-bit load Group
  ////////////////////////////////////////////////

  // LD_dd_(nn)
  m_buffer[0x4b] = EDenums::LD_dd_nn;
  m_buffer[0x5b] = EDenums::LD_dd_nn;
  m_buffer[0x6b] = EDenums::LD_dd_nn;
  m_buffer[0x7b] = EDenums::LD_dd_nn;

  // LD_(nn)_dd
  m_buffer[0x43] = EDenums::LD_nn_dd;
  m_buffer[0x53] = EDenums::LD_nn_dd;
  m_buffer[0x63] = EDenums::LD_nn_dd;
  m_buffer[0x73] = EDenums::LD_nn_dd;

  ////////////////////////////////////////////////
  // Exchange Group
  ////////////////////////////////////////////////

  // LDI
  m_buffer[0xa0] = EDenums::LDI;

  // LDIR
  m_buffer[0xb0] = EDenums::LDIR;

  // LDD
  m_buffer[0xa8] = EDenums::LDD;

  // LDDR
  m_buffer[0xb8] = EDenums::LDDR;

  // CPI
  m_buffer[0xa1] = EDenums::CPI;

  // CPIR
  m_buffer[0xb1] = EDenums::CPIR;

  // CPD
  m_buffer[0xa9] = EDenums::CPD;

  // CPDR
  m_buffer[0xb9] = EDenums::CPDR;

  ////////////////////////////////////////////////
  // 16-bit Arithmetic Group
  ////////////////////////////////////////////////

  // ADC hl ss
  m_buffer[0x4a] = EDenums::ADC_hl_ss;
  m_buffer[0x5a] = EDenums::ADC_hl_ss;
  m_buffer[0x6a] = EDenums::ADC_hl_ss;
  m_buffer[0x7a] = EDenums::ADC_hl_ss;
  
  // SBC hl ss
  m_buffer[0x42] = EDenums::SBC_hl_ss;
  m_buffer[0x52] = EDenums::SBC_hl_ss;
  m_buffer[0x62] = EDenums::SBC_hl_ss;
  m_buffer[0x72] = EDenums::SBC_hl_ss;

  ////////////////////////////////////////////////
  // rotate and shift Group
  ////////////////////////////////////////////////

  // RLD
  m_buffer[0x6f] = EDenums::RLD;

  // RRD
  m_buffer[0x67] = EDenums::RRD;

  ////////////////////////////////////////////////
  // Call Return Group
  ////////////////////////////////////////////////

  // RETI
  m_buffer[0x4d] = EDenums::RETI;

  // RETN
  m_buffer[0x45] = EDenums::RETN;

  ////////////////////////////////////////////////
  // IO Group
  ////////////////////////////////////////////////

  // IN r (C)
  m_buffer[0x70] = EDenums::IN_r_c;
  m_buffer[0x40] = EDenums::IN_r_c;
  m_buffer[0x48] = EDenums::IN_r_c;
  m_buffer[0x50] = EDenums::IN_r_c;
  m_buffer[0x58] = EDenums::IN_r_c;
  m_buffer[0x60] = EDenums::IN_r_c;
  m_buffer[0x68] = EDenums::IN_r_c;
  m_buffer[0x78] = EDenums::IN_r_c;

  // INI
  m_buffer[0xa2] = EDenums::INI;

  // INIR
  m_buffer[0xb2] = EDenums::INIR;

  // IND
  m_buffer[0xaa] = EDenums::IND;

  // INDR
  m_buffer[0xba] = EDenums::INDR;

  // OUT (C), r
  m_buffer[0x41] = EDenums::OUT_c_r;
  m_buffer[0x49] = EDenums::OUT_c_r;
  m_buffer[0x51] = EDenums::OUT_c_r;
  m_buffer[0x59] = EDenums::OUT_c_r;
  m_buffer[0x61] = EDenums::OUT_c_r;
  m_buffer[0x69] = EDenums::OUT_c_r;
  m_buffer[0x79] = EDenums::OUT_c_r;

  // OUTI
  m_buffer[0xa3] = EDenums::OUTI;

  // OTIR
  m_buffer[0xb3] = EDenums::OTIR;

  // OUTD
  m_buffer[0xab] = EDenums::OUTD;

  // OTDR
  m_buffer[0xbb] = EDenums::OTDR;
}

//-------------------------------------------------------------
// Operator overloads
//-------------------------------------------------------------

[[nodiscard]] EDenums 
EDTable::operator[](std::size_t index) const { 
  assert(index < TABLE_SIZE);
  return m_buffer[index];
}

} 

