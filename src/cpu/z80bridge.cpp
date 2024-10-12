#include "z80bridge.hpp"
#include <cstdint>
#include <memory>
#include <stdexcept>

namespace Trpp::CPU{
//-------------------------------------------------------------
//  Lifetime 
//-------------------------------------------------------------

Z80Bridge::Z80Bridge(ZxMemory* memory)
  :
    m_cpu   {std::make_unique<DebugZ80>()},
    m_memory{memory},
    pTable  {std::make_unique<Instructions::NoPrefixTable>()},
    pCBTable{std::make_unique<Instructions::CBTable>()}
{
  m_cpu->ConnectMemory(m_memory);
}

//-------------------------------------------------------------
// Cpu Driving Functions
//-------------------------------------------------------------

void Z80Bridge::Step(){
  // main driving code for the instruction stepped interpreter
  if(NMI()){
    IsHalted() = false; 
    NMI() = false;
    HandleNMI();
  }
  if(INT() && IFF1()){
    IsHalted() = false; 
    INT() = false;
    HandleInterrupt();
  }
  if(IsHalted()){
    m_cpu->NOP();
  }
  std::uint8_t firstByte = NextByteInc();
  switch(firstByte){
    case 0xCB:
    {
      // is CB prefixed
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
        std::uint8_t opcode = PC() + 1;
        StepDDCB(opcode);
        PC() = PC() + 2;
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
        std::uint8_t opcode = PC() + 1;
        StepFDCB(opcode);
        PC() = PC() + 2;
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
// NO PREFIX
// ------------------------------------------------------ //

void Z80Bridge::StepNoPrefix(std::uint8_t opcode){
  enums instruction = (*(pTable))[opcode];
  switch(instruction){
    // ------------------------------------------------------ //
    //  8-bit loads
    // ------------------------------------------------------ //
    case enums::LD_r_r: 
    {
      std::uint8_t ry = opcode & MASK_Y;
      std::uint8_t rz = opcode & MASK_Z;
      m_cpu->LD_r_r(ry, rz);
      break;
    }

    case enums::LD_r_n:
    {
      std::uint8_t secondByte = (*(m_memory))[PC()];
      PC() = PC() + 1;
      std::uint8_t ry = opcode & MASK_Y;
      std::uint8_t n = secondByte;
      m_cpu->LD_r_n(ry, n);
      break;
    }

    case enums::LD_r_hl:
    {
      std::uint8_t ry = opcode & MASK_Y;
      m_cpu->LD_r_hl(ry);
      break;
    }

    case enums::LD_hl_r:
    {
      std::uint8_t rz = opcode & MASK_Z;
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

// CB PREFIX
// ------------------------------------------------------ //

void Z80Bridge::StepCB(std::uint8_t opcode){

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

  // Assumption: On exit, PC points to the next opcode
  using enum DDenums;
  DDenums instruction = (*(pDDTable))[opcode];
  assert(instruction != undefined);
  switch(instruction){

    ///////////////////////////////////
    // 8-bit load group
    ///////////////////////////////////

    case DDenums::LD_r_ixd:
    {
      std::uint8_t r = NextByteInc() & MASK_Y;
      std::uint8_t d = NextByteInc();
      m_cpu->LD_r_ixd(r, d);
      break;
    }

    case DDenums::LD_ixd_r:
    {
      std::uint8_t r = NextByteInc() & MASK_Y;
      std::uint8_t d = NextByteInc();
      m_cpu->LD_r_ixd(r, d);
      break;
    }

    case DDenums::LD_ixd_n:
    {
      std::uint8_t d = NextByteInc();
      std::uint8_t n = NextByteInc();
      m_cpu->LD_ixd_n(d, n);
      break;
    }

    ///////////////////////////////////
    // 16-bit load group
    ///////////////////////////////////

    case DDenums::LD_ix_nn:
    {
      std::uint16_t nn = NextWordInc();
      m_cpu->LD_ix_nn(nn);
      break;
    }

    case DDenums::LD_ix_nn_indirect:
    {
      std::uint16_t nn = NextWordInc();
      m_cpu->LD_ix_nn_indirect(nn);
      break;
    }

    case DDenums::LD_nn_ix_indirect:
    {
      std::uint16_t nn = NextWordInc();
      m_cpu->LD_nn_ix(nn);
      break;
    }

    case DDenums::LD_sp_ix:
    {
      m_cpu->LD_sp_ix();
      break;
    }

    case DDenums::PUSH_ix:
    {
      m_cpu->Push_ix();
      break;
    }

    case DDenums::POP_ix:
    {
      m_cpu->Pop_ix();
      break;
    }

    ///////////////////////////////////
    // exchange group
    ///////////////////////////////////

    case DDenums::EX_sp_ix:
    {
      m_cpu->EX_sp_ix();
      break;
    }

    ///////////////////////////////////
    // 8-bit arithmetic group
    ///////////////////////////////////

    case DDenums::ADD_a_ixd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->ADD_a_ixd(d);
      break;
    }

    case DDenums::ADC_a_ixd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->ADC_a_ixd(d);
      break;
    }

    case DDenums::SUB_a_ixd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->SUB_a_ixd(d);
      break;
    }

    case DDenums::SBC_a_ixd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->SBC_a_ixd(d);
      break;
    }

    case DDenums::AND_a_ixd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->AND_a_ixd(d);
      break;
    }

    case DDenums::OR_a_ixd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->OR_a_ixd(d);
      break;
    }

    case DDenums::XOR_a_ixd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->XOR_a_ixd(d);
      break;
    }

    case DDenums::CP_a_ixd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->CP_a_ixd(d);
      break;
    }

    case DDenums::INC_ixd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->INC_ixd(d);
      break;
    }

    case DDenums::DEC_ixd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->DEC_ixd(d);
      break;
    }

    ///////////////////////////////////
    // 16-bit arithmetic group
    ///////////////////////////////////

    /*
    case DDenums::ADD_ix_pp:
    {
      std::uint8_t pp = NextByteInc() & MASK_P;
      m_cpu->ADD16_ix_pp_ixd(pp);
      break;
    }
    */

    case DDenums::INC_ix:
    {
      m_cpu->INC16_ix();
      break;
    }

    case DDenums::DEC_ix:
    {
      m_cpu->DEC16_ix();
      break;
    }

    ///////////////////////////////////
    // Jump Group
    ///////////////////////////////////

    case DDenums::JP_ix:
    {
      m_cpu->JP_ix();
      break;
    }

    case DDenums::undefined: [[fallthrough]];
    default:
    {
      throw std::runtime_error{"Undefined instruction enum"};
    }
  }
}

// DDCB PREFIX
// ------------------------------------------------------ //

void Z80Bridge::StepDDCB(std::uint8_t opcode){
  // Assumption: On exit, PC points to the next opcode
  using enum DDCBenums;
  DDCBenums instruction = (*(pDDCBTable))[opcode];
  assert(instruction != undefined);
  switch(instruction){

    // Rotate Shift Group

  }
}

// FD PREFIX
// ------------------------------------------------------ //

void Z80Bridge::StepFD(std::uint8_t opcode){
  throw std::runtime_error{
        std::format("Error::StepFD::Unimplemented")
  };
}

// FDCB PREFIX
// ------------------------------------------------------ //

void Z80Bridge::StepFDCB(std::uint8_t opcode){
  throw std::runtime_error{
        std::format("Error::StepFDCB::Unimplemented")
  };
}

// ------------------------------------------------------ //
// Interrupt behavioural code
// ------------------------------------------------------ //

void Z80Bridge::HandleNMI(){
  // Reference: Zilog Z80 p.200
  IFF2() = IFF1();
  IFF1() = false;
  m_cpu->CALL_nn(0x0066);
}

void Z80Bridge::HandleInterrupt(){
  // Reference: Zilog Z80 p.200
  IFF1() = false;
  IFF2() = false;
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
      m_cpu->CALL_nn(0x0038);
      break;
    }
    case Z80::InterruptMode::mode2:
    {
      // int mode 2 requires a byte from the interrupting device
      // for now i put it in the last read data members
      std::uint16_t intVector = I() << 8;
      intVector |= LastRead();
      m_cpu->CALL_nn(intVector);
      break;
    }
  }
}


} // namespace Trpp::Cpu
