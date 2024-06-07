#include "z80.hpp"

namespace cpu{
  void Z80::Decode(){

  }

  void DebugZ80::SetInstruction(std::uint8_t* position){
    m_instruction = position;
  }

  void DebugZ80::SetInstruction(const Instruction& inst){
    m_instruction = inst;
  }

  void DebugZ80::PrintInstruction() const{
    std::cout << m_instruction << '\n';
  }
}
