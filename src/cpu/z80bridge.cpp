#include "z80bridge.hpp"
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace trpp{
//-------------------------------------------------------------
//  Lifetime 
//-------------------------------------------------------------

Z80Bridge::Z80Bridge(ZxMemory* memory)
  :
    m_cpu   {std::make_unique<DebugZ80>()},
    m_memory{memory},
    pTable  {std::make_unique<instructions::NoPrefixTable>()},
    pCBTable{std::make_unique<instructions::CBTable>()}
{
  m_cpu->ConnectMemory(m_memory);
}

//-------------------------------------------------------------
// Cpu Driving Functions
//-------------------------------------------------------------

void Z80Bridge::Step(){
  // main driving code for the instruction stepped interpreter
  if(NMI()){
    NMI() = false;
    HandleInterrupt();
  }
  if(INT() && IFF1() && IFF2()){
    INT() = false;
    HandleInterrupt();
  }
  std::uint8_t firstByte = NextByteInc();
  switch(firstByte){
    case 0xCB:
    {
      // prefixed with CB
      std::uint8_t opcodeByte = NextByteInc();
      StepCB(opcodeByte);
      break;
    }
    case 0xED:
    {
      // is ED prefixed
      std::uint8_t opcodeByte = NextByteInc();
      StepED(opcodeByte);
      break;
    }
    case 0xDD:
    {
      // is DD prefixed
      std::uint8_t secondByte = NextByteInc();
      if(secondByte == 0xCB){
        std::uint8_t opcode = NextByteInc();
        StepDDCB(opcode);
      }
      else{
        StepDD(secondByte);
      }
      break;
    }
    case 0xFD:
    {
      // is FD prefixed
      std::uint8_t secondByte = NextByteInc();
      if(secondByte == 0xCB){
        std::uint8_t opcode = NextByteInc();
        StepFDCB(opcode);
      }
      else{
        StepFD(secondByte);
      }
      break;
    }
    default:
    {
      // does not have a prefix
      StepNoPrefix(firstByte);
      break;
    }
  }
}

// ------------------------------------------------------ //
//  Per prefix handler
// ------------------------------------------------------ //

// CB PREFIX
// ------------------------------------------------------ //

void Z80Bridge::StepCB(std::uint8_t opcode){
  using trpp::instructions::CBenums;
  CBenums instruction = (*(pCBTable))[opcode];
  throw std::runtime_error{
        std::format("Error::StepCB::Unimplemented")
  };
  switch(instruction){
    case CBenums::undefined:
      [[fallthrough]];
    default:
    {
      throw std::runtime_error{
        std::format("Error::Opcode::{0}::UNKNOWN", opcode)
      };
    }
  }
}

// ED PREFIX
// ------------------------------------------------------ //

void Z80Bridge::StepED(std::uint8_t opcode){
  throw std::runtime_error{
        std::format("Error::StepED::Unimplemented")
  };
}

// DD PREFIX
// ------------------------------------------------------ //

void Z80Bridge::StepDD(std::uint8_t opcode){
  throw std::runtime_error{
        std::format("Error::StepDD::Unimplemented")
  };
}

void Z80Bridge::StepDDCB(std::uint8_t opcode){
  throw std::runtime_error{
        std::format("Error::StepDDCB::Unimplemented")
  };
}

// FD PREFIX
// ------------------------------------------------------ //

void Z80Bridge::StepFD(std::uint8_t opcode){
  throw std::runtime_error{
        std::format("Error::StepFD::Unimplemented")
  };
}

void Z80Bridge::StepFDCB(std::uint8_t opcode){
  throw std::runtime_error{
        std::format("Error::StepFDCB::Unimplemented")
  };
}

// NO PREFIX
// ------------------------------------------------------ //

void Z80Bridge::StepNoPrefix(std::uint8_t opcode){
  using trpp::instructions::enums;
  enums instruction = (*(pTable))[opcode];
  switch(instruction){
    // ------------------------------------------------------ //
    //  8-bit loads
    // ------------------------------------------------------ //
    case enums::LD_r_r: 
    {
      std::uint8_t ry = opcode & maskY;
      std::uint8_t rz = opcode & maskZ;
      m_cpu->LD_r_r(ry, rz);
      break;
    }

    case enums::LD_r_n:
    {
      std::uint8_t secondByte = (*(m_memory))[PC()];
      PC() = PC() + 1;
      std::uint8_t ry = opcode & maskY;
      std::uint8_t n = secondByte;
      m_cpu->LD_r_n(ry, n);
      break;
    }

    case enums::LD_r_hl:
    {
      std::uint8_t ry = opcode & maskY;
      m_cpu->LD_r_hl(ry);
      break;
    }

    case enums::LD_hl_r:
    {
      std::uint8_t rz = opcode & maskZ;
      m_cpu->LD_hl_r(rz);
      break;
    }

    case enums::LD_hl_n:
    {
      std::uint8_t n = NextByteInc();
      m_cpu->LD_hl_n(n);
      break;
    }
  
    case enums::LD_a_bc:
    {
      m_cpu->LD_a_bc();
      break;
    }

    case enums::LD_a_de:
    {
      m_cpu->LD_a_de();
      break;
    }

    case enums::LD_a_nn:
    {
      std::uint16_t nn = NextWordInc();
      m_cpu->LD_a_nn(nn);
      break;
    }

    case enums::LD_bc_a:
    {
      m_cpu->LD_bc_a();
      break;
    }

    case enums::LD_de_a:
    {
      m_cpu->LD_de_a();
      break;
    }

    case enums::LD_nn_a:
    {
      std::uint16_t nn = NextWordInc();
      m_cpu->LD_nn_a(nn);
      break;
    }

    // ------------------------------------------------------ //
    //  16-bit loads
    // ------------------------------------------------------ //

    case enums::NOP:
    {
      m_cpu->NOP();
      return;
    }

    // ------------------------------------------------------ //
    //  Error in decoding
    // ------------------------------------------------------ //

    case enums::Undefined:
      [[fallthrough]];
    default:{
      throw std::runtime_error{
        std::format("Error::Opcode::{0}::UNKNOWN", opcode)
      };
    }
  }
}

// ------------------------------------------------------ //
// Interrupt behavioural code
// ------------------------------------------------------ //

void Z80Bridge::HandleInterrupt(){
  // Reference: Zilog Z80 p.200
  auto interruptMode = IntMode();
  switch(interruptMode){
    case Z80::InterruptMode::mode0:
    {
      // Zx spectrum does not use int mode 0 (?)
      throw UnimplementedError{};
      break;
    }
    case Z80::InterruptMode::mode1:
    {
      // int mode 1 just sets pc to 0x0038
      PC() = 0x0038;
      break;
    }
    case Z80::InterruptMode::mode2:
    {
      // int mode 2 requires a byte from the interrupting device
      // for now i put it in the last read data members
      std::uint16_t intVector = I() << 8;
      intVector |= LastRead();
      PC() = intVector;
      break;
    }
  }
}

}
