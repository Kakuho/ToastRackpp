#include "z80bridge.hpp"
#include "cpu/instruction_tables/enums/cbenums.hpp"
#include "cpu/instruction_tables/enums/enums.hpp"
#include <memory>

namespace trpp{
//-------------------------------------------------------------
//  Lifetime 
//-------------------------------------------------------------

Z80Bridge::Z80Bridge(ZxMemory* memory)
  :
    m_cpu{std::make_unique<Z80>()},
    m_memory{memory}
{
  m_cpu->ConnectMemory(m_memory);
}

//-------------------------------------------------------------
// Cpu Driving Functions
//-------------------------------------------------------------

void Z80Bridge::Tick(){
  // instruction stepped interpreter

  std::uint8_t byteInitial = (*(m_memory))[PC()];
  PC() = PC() + 1;
  switch(byteInitial){
    case 0xCB:
    {
      // prefixed with CB
      std::uint8_t opcodeByte = (*(m_memory))[PC()];
      PC() = PC() + 1;
      TickCBPrefix(opcodeByte);
      break;
    }
    case 0xED:
      // is ED prefixed
      break;
    case 0xDD:
      // is DD prefixed
      break;
    case 0xFD:
      // is FD prefixed
      break;
    default:
    {
      // does not have a prefix
      TickNoPrefix(byteInitial);
      break;
    }
  }
}

// ------------------------------------------------------ //
//  Per prefix handler
// ------------------------------------------------------ //

void Z80Bridge::TickCBPrefix(std::uint8_t opcode){
  using trpp::instructions::CBenums;
  CBenums instruction = (*(pCBTable))[opcode];
  switch(instruction){
    case CBenums::undefined:
      throw std::runtime_error{
        std::format("Error::Opcode::{0}::UNKNOWN", opcode)
      };
  }
}

void Z80Bridge::TickNoPrefix(std::uint8_t opcode){
  using trpp::instructions::enums;
  enums instruction = (*(pTable))[opcode];
  switch(instruction){
    case enums::NOP:
    {
      m_cpu->NOP();
      return;
    }
    case enums::LD_r_n: 
    {
      std::uint8_t n = (*(m_memory))[PC()];
      m_cpu->LD_r_n(opcode & maskP, n);
      return;
    }
    case enums::Undefined:
      [[fallthrough]];
    default:{
      throw std::runtime_error{
        std::format("Error::Opcode::{0}::UNKNOWN", opcode)
      };
    }
  }
}

}
