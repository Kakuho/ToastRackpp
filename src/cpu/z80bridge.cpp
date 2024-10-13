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
  // instruction stepping routine
  // intermediateSet is used in 0xDD or 0xFD to check if they 
  // need skipping
  static std::unordered_set<std::uint8_t> intermediateSet = {
    0xDD, 0xED, 0xFD
  };
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
        PC() = PC() + 1;
        break;
      }
      else if(intermediateSet.contains(secondByte)){
        break;
      }

      else{
        StepDD(secondByte);
        break;
      }
    }
    case 0xFD:
    {
      // is FD prefixed
      std::uint8_t secondByte = NextByteInc();
      if(secondByte == 0xCB){
        std::uint8_t opcode = PC() + 1;
        StepFDCB(opcode);
        PC() = PC() + 2;
        break;
      }
      else if(intermediateSet.contains(secondByte)){
        break;
      }
      else{
        StepFD(secondByte);
        break;
      }
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

    //-------------------------------------------------------------
    // 8-bit load group
    //-------------------------------------------------------------

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

    //-------------------------------------------------------------
    // 16-bit load group
    //-------------------------------------------------------------

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

    //-------------------------------------------------------------
    // exchange group
    //-------------------------------------------------------------

    case DDenums::EX_sp_ix:
    {
      m_cpu->EX_sp_ix();
      break;
    }

    //-------------------------------------------------------------
    // 8-bit arithmetic group
    //-------------------------------------------------------------

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

    //-------------------------------------------------------------
    // 16-bit arithmetic group
    //-------------------------------------------------------------

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

    //-------------------------------------------------------------
    // Jump Group
    //-------------------------------------------------------------

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
  // Assumption: 
  //  On Enter, PC points to the parameter d
  //  PC is not changed in the execution of this function
  using enum DDCBenums;
  DDCBenums instruction = (*(pDDCBTable))[opcode];
  assert(instruction != undefined);
  switch(instruction){

    //-------------------------------------------------------------
    // Rotate Shift Group
    //-------------------------------------------------------------
    
    case DDCBenums::RLC_ixd:
    {
      std::uint8_t d = GetByte(PC());
      m_cpu->RLC_ixd(d);
      break;
    }

    case DDCBenums::RL_ixd:
    {
      std::uint8_t d = GetByte(PC());
      m_cpu->RL_ixd(d);
      break;
    }

    case DDCBenums::RRC_ixd:
    {
      std::uint8_t d = GetByte(PC());
      m_cpu->RRC_ixd(d);
      break;
    }

    case DDCBenums::RR_ixd:
    {
      std::uint8_t d = GetByte(PC());
      m_cpu->RR_ixd(d);
      break;
    }

    case DDCBenums::SLA_ixd:
    {
      std::uint8_t d = GetByte(PC());
      m_cpu->SLA_ixd(d);
      break;
    }

    case DDCBenums::SRA_ixd:
    {
      std::uint8_t d = GetByte(PC());
      m_cpu->SRA_ixd(d);
      break;
    }

    case DDCBenums::SRL_ixd:
    {
      std::uint8_t d = GetByte(PC());
      m_cpu->SRL_ixd(d);
      break;
    }

    //-------------------------------------------------------------
    // Bit set group
    //-------------------------------------------------------------
    
    case DDCBenums::BIT_b_ixd:
    {
      std::uint8_t d = GetByte(PC());
      std::uint8_t b = GetByte(PC() + 1) >> 3;
      m_cpu->BIT_b_ixd(b, d);
      break;
    }

    case DDCBenums::SET_b_ixd:
    {
      std::uint8_t d = GetByte(PC());
      std::uint8_t b = GetByte(PC() + 1) >> 3;
      m_cpu->SET_b_ixd(b, d);
      break;
    }

    case DDCBenums::RES_b_ixd:
    {
      std::uint8_t d = GetByte(PC());
      std::uint8_t b = GetByte(PC() + 1) >> 3;
      m_cpu->RES_b_ixd(b, d);
      break;
    }
  }
}


// FD PREFIX
// ------------------------------------------------------ //
void Z80Bridge::StepFD(std::uint8_t opcode){
  // Assumption: On exit, PC points to the next opcode
  using enum FDenums;
  FDenums instruction = (*(pFDTable))[opcode];
  assert(instruction != undefined);
  switch(instruction){

    //-------------------------------------------------------------
    // 8-bit load group
    //-------------------------------------------------------------

    case FDenums::LD_r_iyd:
    {
      std::uint8_t r = NextByteInc() & MASK_Y;
      std::uint8_t d = NextByteInc();
      m_cpu->LD_r_iyd(r, d);
      break;
    }

    case FDenums::LD_iyd_r:
    {
      std::uint8_t r = NextByteInc() & MASK_Y;
      std::uint8_t d = NextByteInc();
      m_cpu->LD_r_iyd(r, d);
      break;
    }

    case FDenums::LD_iyd_n:
    {
      std::uint8_t d = NextByteInc();
      std::uint8_t n = NextByteInc();
      m_cpu->LD_iyd_n(d, n);
      break;
    }

    //-------------------------------------------------------------
    // 16-bit load group
    //-------------------------------------------------------------

    case FDenums::LD_iy_nn:
    {
      std::uint16_t nn = NextWordInc();
      m_cpu->LD_iy_nn(nn);
      break;
    }

    case FDenums::LD_iy_nn_indirect:
    {
      std::uint16_t nn = NextWordInc();
      m_cpu->LD_iy_nn_indirect(nn);
      break;
    }

    case FDenums::LD_nn_iy_indirect:
    {
      std::uint16_t nn = NextWordInc();
      m_cpu->LD_nn_iy(nn);
      break;
    }

    case FDenums::LD_sp_iy:
    {
      m_cpu->LD_sp_iy();
      break;
    }

    case FDenums::PUSH_iy:
    {
      m_cpu->Push_iy();
      break;
    }

    case FDenums::POP_iy:
    {
      m_cpu->Pop_iy();
      break;
    }

    //-------------------------------------------------------------
    // exchange group
    //-------------------------------------------------------------

    case FDenums::EX_sp_iy:
    {
      m_cpu->EX_sp_iy();
      break;
    }

    //-------------------------------------------------------------
    // 8-bit arithmetic group
    //-------------------------------------------------------------

    case FDenums::ADD_a_iyd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->ADD_a_iyd(d);
      break;
    }

    case FDenums::ADC_a_iyd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->ADC_a_iyd(d);
      break;
    }

    case FDenums::SUB_a_iyd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->SUB_a_iyd(d);
      break;
    }

    case FDenums::SBC_a_iyd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->SBC_a_iyd(d);
      break;
    }

    case FDenums::AND_a_iyd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->AND_a_iyd(d);
      break;
    }

    case FDenums::OR_a_iyd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->OR_a_iyd(d);
      break;
    }

    case FDenums::XOR_a_iyd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->XOR_a_iyd(d);
      break;
    }

    case FDenums::CP_a_iyd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->CP_a_iyd(d);
      break;
    }

    case FDenums::INC_iyd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->INC_iyd(d);
      break;
    }

    case FDenums::DEC_iyd:
    {
      std::uint8_t d = NextByteInc();
      m_cpu->DEC_iyd(d);
      break;
    }

    //-------------------------------------------------------------
    // 16-bit arithmetic group
    //-------------------------------------------------------------

    /*
    case FDenums::ADD_iy_pp:
    {
      std::uint8_t pp = NextByteInc() & MASK_P;
      m_cpu->AFD16_iy_pp_ixd(pp);
      break;
    }
    */

    case FDenums::INC_iy:
    {
      m_cpu->INC16_iy();
      break;
    }

    case FDenums::DEC_iy:
    {
      m_cpu->DEC16_iy();
      break;
    }

    //-------------------------------------------------------------
    // Jump Group
    //-------------------------------------------------------------

    case FDenums::JP_iy:
    {
      m_cpu->JP_iy();
      break;
    }

    case FDenums::undefined: [[fallthrough]];
    default:
    {
      throw std::runtime_error{"Undefined instruction enum"};
    }
  }
}

// FDCB PREFIX
// ------------------------------------------------------ //

void Z80Bridge::StepFDCB(std::uint8_t opcode){
  // Assumption: 
  //  On Enter, PC points to the parameter d
  //  PC is not changed in the execution of this function
  using enum FDCBenums;
  FDCBenums instruction = (*(pFDCBTable))[opcode];
  assert(instruction != undefined);
  switch(instruction){

    //-------------------------------------------------------------
    // Rotate Shift Group
    //-------------------------------------------------------------
    
    case FDCBenums::RLC_iyd:
    {
      std::uint8_t d = GetByte(PC());
      m_cpu->RLC_iyd(d);
      break;
    }

    case FDCBenums::RL_iyd:
    {
      std::uint8_t d = GetByte(PC());
      m_cpu->RL_iyd(d);
      break;
    }

    case FDCBenums::RRC_iyd:
    {
      std::uint8_t d = GetByte(PC());
      m_cpu->RRC_iyd(d);
      break;
    }

    case FDCBenums::RR_iyd:
    {
      std::uint8_t d = GetByte(PC());
      m_cpu->RR_iyd(d);
      break;
    }

    case FDCBenums::SLA_iyd:
    {
      std::uint8_t d = GetByte(PC());
      m_cpu->SLA_iyd(d);
      break;
    }

    case FDCBenums::SRA_iyd:
    {
      std::uint8_t d = GetByte(PC());
      m_cpu->SRA_iyd(d);
      break;
    }

    case FDCBenums::SRL_iyd:
    {
      std::uint8_t d = GetByte(PC());
      m_cpu->SRL_iyd(d);
      break;
    }

    //-------------------------------------------------------------
    // Bit set group
    //-------------------------------------------------------------
    
    case FDCBenums::BIT_b_iyd:
    {
      std::uint8_t d = GetByte(PC());
      std::uint8_t b = GetByte(PC() + 1) >> 3;
      m_cpu->BIT_b_iyd(b, d);
      break;
    }

    case FDCBenums::SET_b_iyd:
    {
      std::uint8_t d = GetByte(PC());
      std::uint8_t b = GetByte(PC() + 1) >> 3;
      m_cpu->SET_b_iyd(b, d);
      break;
    }

    case FDCBenums::RES_b_iyd:
    {
      std::uint8_t d = GetByte(PC());
      std::uint8_t b = GetByte(PC() + 1) >> 3;
      m_cpu->RES_b_iyd(b, d);
      break;
    }
  }
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
