#include "z80.hpp"
#include <cstdint>
#include <stdexcept>

namespace trpp{

void Z80::Decode(){

}

//---------------------------------------------------------------//
// OPCODE INSTRUCTIONS 
//---------------------------------------------------------------//
//
//---------------------------------------------------------------//
// Z80 - No PREFIX
//---------------------------------------------------------------//


void Z80::EX_AF_AF2(){
  // opcode = 00'0001'000 = 0x08
  std::uint16_t af = m_regs.af1;
  std::uint16_t af2 = m_regs.af2;
  // exchange the registers
  m_regs.af1 = af2;
  m_regs.af2 = af;
}

void Z80::LD_dd_nn(std::uint8_t dd, std::uint8_t n1, std::uint8_t n2){
std::uint16_t nn = formWord(n1, n2);
  switch(dd){
    case 0b00:
      m_regs.bc1 = nn;
    break;
    case 0b01:
      m_regs.de1 = nn;
    break;
    case 0b10:
      m_regs.hl1 = nn;
    break;
    case 0b11:
      m_regs.sp = nn;
    break;
    default:
      throw std::runtime_error{"error! failed to decode reg pair in ld_dd_nn"};
    break;
  }
}

void Z80::LD_r_r(std::uint8_t r, std::uint8_t rp){
  std::uint8_t& dest = registerTable(r);
  const std::uint8_t& src = registerTable(rp);
  dest = src;
}

void Z80::LD_r_n(std::uint8_t r, std::uint8_t n){
  std::uint8_t& dest = registerTable(r);
  dest = n;
}

//---------------------------------------------------------------//
// DebugZ80 - No PREFIX
//---------------------------------------------------------------//

void DebugZ80::EX_AF_AF2(){
  logger.StartInstruction(m_regs, CpuLogger::NoPrefix::EX_AF_AF2);
  Z80::EX_AF_AF2();
  logger.EndInstruction(m_regs, CpuLogger::NoPrefix::EX_AF_AF2);
}

void DebugZ80::LD_dd_nn(std::uint8_t dd, std::uint8_t n1, std::uint8_t n2){
  logger.StartInstruction(m_regs, CpuLogger::NoPrefix::EX_AF_AF2);
  Z80::LD_dd_nn(dd, n1, n2);
  logger.EndInstruction(m_regs, CpuLogger::NoPrefix::EX_AF_AF2);
}

} // namespace trpp

