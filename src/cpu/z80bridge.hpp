#ifndef CPU_Z80BRIDGE_HPP 
#define CPU_Z80BRIDGE_HPP

// Class to represent the driving class of a z80 cpu and 
// connections to the other emulated systems
//
// the cpu core functionalities is within class Z80

#include <memory>

#include "cpu/instruction_tables/enums/cbenums.hpp"
#include "cpu/instruction_tables/enums/enums.hpp"
#include "z80.hpp"
#include "shared/zxmemory.hpp"

namespace trpp{

class Z80Bridge{
  struct DecodeError{};
  struct UnimplementedError{};
  public:
    //-------------------------------------------------------------
    //  Lifetime
    //-------------------------------------------------------------

    Z80Bridge(ZxMemory* memory);

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

    // ------------------------------------------------------ //
    //  Memory Addressing
    // ------------------------------------------------------ //

    std::uint8_t NextByteInc(){
      std::uint8_t byte = (*(m_memory))[PC()];
      PC() = PC() + 1;
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
    static constexpr std::uint8_t maskX = 0b1100'0000;
    static constexpr std::uint8_t maskY = 0b0011'1000;
    static constexpr std::uint8_t maskZ = 0b0000'0111;
    static constexpr std::uint8_t maskP = 0b0011'0000;
    static constexpr std::uint8_t maskQ = 0b0000'1000;

    void Step();

  private:
    // these are helper functions for Tick()
    void StepCBPrefix(std::uint8_t opcode);
    void StepNoPrefix(std::uint8_t opcode);

  public:
    // ------------------------------------------------------ //
    // Interrupt behavioural code
    // ------------------------------------------------------ //
    
    void TriggerNmi(){NMI() = true;}
    void TriggerInt(){INT() = true;}
    void HandleInterrupt();

  private:
    // internal data representation
    std::unique_ptr<Z80> m_cpu;
    ZxMemory* m_memory;

    // instruction tables
    std::unique_ptr<instructions::NoPrefixTable> pTable;
    std::unique_ptr<instructions::CBTable> pCBTable;
    // cycle tables

};

} // namespace Trpp

#endif
