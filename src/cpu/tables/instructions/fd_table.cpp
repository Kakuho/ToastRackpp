#include "fd_table.hpp"

namespace Trpp::CPU::Instructions{

//-------------------------------------------------------------
// lifetime
//-------------------------------------------------------------

FDTable::FDTable(): m_buffer{}{
  m_buffer.fill(FDenums::undefined);
  SetEntries();
}

//-------------------------------------------------------------
// Operational
//-------------------------------------------------------------

void FDTable::SetEntries() noexcept{
  using enum FDenums;

  ////////////////////////////////////////////////
  // 8-bit Load Group
  ////////////////////////////////////////////////

  // LD r, (iy + d)
  m_buffer[0x46] = FDenums::LD_r_iyd;
  m_buffer[0x4e] = FDenums::LD_r_iyd;
  m_buffer[0x56] = FDenums::LD_r_iyd;
  m_buffer[0x5e] = FDenums::LD_r_iyd;
  m_buffer[0x66] = FDenums::LD_r_iyd;
  m_buffer[0x6e] = FDenums::LD_r_iyd;
  m_buffer[0x7e] = FDenums::LD_r_iyd;

  // LD (iy + d), r
  m_buffer[0x70] = FDenums::LD_iyd_r;
  m_buffer[0x71] = FDenums::LD_iyd_r;
  m_buffer[0x72] = FDenums::LD_iyd_r;
  m_buffer[0x73] = FDenums::LD_iyd_r;
  m_buffer[0x74] = FDenums::LD_iyd_r;
  m_buffer[0x75] = FDenums::LD_iyd_r;
  m_buffer[0x77] = FDenums::LD_iyd_r;

  // LD (iy + d), n
  m_buffer[0x36] = FDenums::LD_iyd_n;

  ////////////////////////////////////////////////
  // 16-bit Load Group
  ////////////////////////////////////////////////

  // LD iy, nn
  m_buffer[0x21] = FDenums::LD_iy_nn;

  // LD iy, (nn)
  m_buffer[0x2a] = FDenums::LD_iy_nn_indirect;

  // LD (nn) iy
  m_buffer[0x22] = FDenums::LD_nn_iy_indirect;

  // LD sp, iy
  m_buffer[0xf9] = FDenums::LD_sp_iy;

  // Push IX
  m_buffer[0xe5] = FDenums::PUSH_iy;

  // Pop iy
  m_buffer[0xe1] = FDenums::POP_iy;

  ////////////////////////////////////////////////
  // Exchange Group
  ////////////////////////////////////////////////

  // Ex sp iy
  m_buffer[0xe3] = FDenums::EX_sp_iy;

  ////////////////////////////////////////////////
  // 8-bit Arithmetic Group
  ////////////////////////////////////////////////

  // AFD a, iy+d
  m_buffer[0x86] = FDenums::ADD_a_iyd;

  // ADC a, iy + d
  m_buffer[0x8e] = FDenums::ADC_a_iyd;

  // SUB a, iy + d
  m_buffer[0x96] = FDenums::SUB_a_iyd;

  // SBC a, iy + d
  m_buffer[0x9e] = FDenums::SBC_a_iyd;

  // AND a, iy + d
  m_buffer[0xa6] = FDenums::AND_a_iyd;

  // OR a, iy + d
  m_buffer[0xb6] = FDenums::OR_a_iyd;

  // XOR a, iy + d
  m_buffer[0xae] = FDenums::XOR_a_iyd;

  // CP a, iy + d
  m_buffer[0xbe] = FDenums::CP_a_iyd;

  // INC iy + d
  m_buffer[0x34] = FDenums::INC_iyd;

  // DEC iy + d
  m_buffer[0x35] = FDenums::DEC_iyd;

  ////////////////////////////////////////////////
  // 16-bit Arithmetic Group
  ////////////////////////////////////////////////

  // Add iy pp
  m_buffer[0x09] = FDenums::ADD_iy_rr;
  m_buffer[0x19] = FDenums::ADD_iy_rr;
  m_buffer[0x29] = FDenums::ADD_iy_rr;
  m_buffer[0x39] = FDenums::ADD_iy_rr;

  // INC iy
  m_buffer[0x23] = FDenums::INC_iy;

  // DEC iy
  m_buffer[0x2b] = FDenums::DEC_iy;

  ////////////////////////////////////////////////
  // Jump Group
  ////////////////////////////////////////////////

  m_buffer[0xe9] = FDenums::JP_iy;
}

//-------------------------------------------------------------
// Operator overloads
//-------------------------------------------------------------

[[nodiscard]] FDenums 
FDTable::operator[](std::size_t index) const { 
  assert(index < TABLE_SIZE);
  return m_buffer[index];
}

} 
