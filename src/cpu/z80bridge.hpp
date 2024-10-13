#ifndef CPU_Z80BRIDGE_HPP 
#define CPU_Z80BRIDGE_HPP

// Class to represent the driving class of a z80 cpu and 
// connections to the other emulated systems
//
// the cpu core functionalities is within class Z80
//
// NOTE: The cpu it uses is a DebugZ80! this is so we can check its 
//       internal state.
//       It should be easy to replace it for a Z80 later on.
//
//       (Maybe it's better to create a friend observer class instead 
//       of needing to plug in and out via source code modification?)

#include <memory>
#include <unordered_set>

#include "cpu/tables/enums/enums.hpp"
#include "cpu/tables/enums/cb_enums.hpp"
#include "cpu/tables/enums/dd_enums.hpp"
#include "cpu/tables/enums/ddcb_enums.hpp"
#include "cpu/tables/enums/fd_enums.hpp"
#include "cpu/tables/enums/fdcb_enums.hpp"

#include "cpu/tables/instructions/noprefix_table.hpp"
#include "cpu/tables/instructions/cb_table.hpp"
#include "cpu/tables/instructions/dd_table.hpp"
#include "cpu/tables/instructions/ddcb_table.hpp"
#include "cpu/tables/instructions/fd_table.hpp"
#include "cpu/tables/instructions/fdcb_table.hpp"

#include "debugz80.hpp"
#include "shared/zxmemory.hpp"

namespace Trpp::CPU{

class Z80Bridge{
  struct DecodeError{};
  struct UnimplementedError{};
  public:
    //-------------------------------------------------------------
    //  Lifetime
    //-------------------------------------------------------------

    explicit Z80Bridge(ZxMemory* memory);

    // ------------------------------------------------------ //
    //  Interface with registers
    // ------------------------------------------------------ //

    Z80RegisterPair& PC(){ return m_cpu->m_regs.pc;}
    const Z80RegisterPair& PC() const{ return m_cpu->m_regs.pc;}

    std::uint8_t& I(){ return m_cpu->m_regs.i;}
    const std::uint8_t& I() const{ return m_cpu->m_regs.i;}

    std::uint8_t& LastRead(){ return m_cpu->m_lastRead;}
    const std::uint8_t& LastRead() const { return m_cpu->m_lastRead;}

    // for interrupts
    bool& IFF1(){ return m_cpu->m_iff1;}
    const bool& IFF1() const{ return m_cpu->m_iff1;}

    bool& IFF2(){ return m_cpu->m_iff2;}
    const bool& IFF2() const{ return m_cpu->m_iff2;}

    bool& NMI(){ return m_cpu->m_nmi;}
    const bool& NMI() const{ return m_cpu->m_nmi;}


    bool& INT(){ return m_cpu->m_int;}
    const bool& INT() const{ return m_cpu->m_int;}

    Z80::InterruptMode& IntMode(){ return m_cpu->m_imode;}
    const Z80::InterruptMode& IntMode() const{ return m_cpu->m_imode;}

    bool& IsHalted(){ return m_cpu->m_halted;}
    const bool& IsHalted() const{ return m_cpu->m_halted;}

    // ------------------------------------------------------ //
    //  Memory Addressing
    // ------------------------------------------------------ //

    std::uint8_t NextByteInc(){
      std::uint8_t byte = (*(m_memory))[PC()];
      PC() = PC() + 1;
      return byte;
    }

    constexpr std::uint8_t GetByte(std::uint16_t index) const{
      std::uint8_t byte = (*(m_memory))[index];
      return byte;
    }

    std::uint16_t NextWordInc(){
      std::uint16_t word = m_cpu->ReadWord(PC());
      PC() = PC() + 2;
      return word;
    }

    //-------------------------------------------------------------
    //  Cpu Driving Functions
    //-------------------------------------------------------------

    // Masks useful for decoding instructions
    static constexpr std::uint8_t MASK_X = 0b1100'0000;
    static constexpr std::uint8_t MASK_Y = 0b0011'1000;
    static constexpr std::uint8_t MASK_Z = 0b0000'0111;
    static constexpr std::uint8_t MASK_P = 0b0011'0000;
    static constexpr std::uint8_t MASK_Q = 0b0000'1000;

    void Step();

  private:
    // these are helper functions for Tick()
    void StepNoPrefix(std::uint8_t opcode);
    void StepCB(std::uint8_t opcode);
    void StepED(std::uint8_t opcode);
    void StepDD(std::uint8_t opcode);
    void StepDDCB(std::uint8_t opcode);
    void StepFD(std::uint8_t opcode);
    void StepFDCB(std::uint8_t opcode);

  public:
    // ------------------------------------------------------ //
    // Interrupt behavioural code
    // ------------------------------------------------------ //
    
    void TriggerNmi(){NMI() = true;}
    void TriggerInt(){INT() = true;}

    void HandleNMI();
    void HandleInterrupt();

  private:
    // internal data representation
    std::unique_ptr<DebugZ80> m_cpu;
    ZxMemory* m_memory;

    // instruction tables
    std::unique_ptr<Instructions::NoPrefixTable> pTable;
    std::unique_ptr<Instructions::CBTable> pCBTable;
    std::unique_ptr<Instructions::DDTable> pDDTable;
    std::unique_ptr<Instructions::DDCBTable> pDDCBTable;
    std::unique_ptr<Instructions::FDTable> pFDTable;
    std::unique_ptr<Instructions::FDCBTable> pFDCBTable;

    // cycle tables

};

} // namespace Trpp::Cpu

#endif
