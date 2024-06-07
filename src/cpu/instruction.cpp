#include "instruction.hpp"
#include <initializer_list>

namespace cpu{
  Instruction::Instruction(std::uint8_t* pos): 
  m_pos{pos}{

  }

  void Instruction::operator=(std::uint8_t* pos){
    m_pos = pos;
  }

  void Instruction::Read(){
    std::uint8_t header = *m_pos;
    switch(header){
      case 0x00:
      break;

    }
  }

  InstructionROM::InstructionROM(std::initializer_list<std::uint8_t> values):
    buffer{values}{
  }
} // namespace cpu
