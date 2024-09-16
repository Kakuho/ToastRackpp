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

    //-------------------------------------------------------------
    //  Cpu Driving Functions
    //-------------------------------------------------------------

    // Masks useful for decoding instructions
    static constexpr std::uint8_t maskX = 0b1100'0000;
    static constexpr std::uint8_t maskY = 0b0011'1000;
    static constexpr std::uint8_t maskZ = 0b0000'0111;
    static constexpr std::uint8_t maskP = 0b0011'0000;
    static constexpr std::uint8_t maskQ = 0b0000'1000;

    void Tick();
    void TickCBPrefix(std::uint8_t opcode);
    void TickCBPrefix(instructions::CBenums);
    void TickNoPrefix(std::uint8_t opcode);
    void TickNoPrefix(instructions::enums);

    std::uint8_t FetchNN();

    // ------------------------------------------------------ //
    //  Classical functions
    // ------------------------------------------------------ //

    void Fetch();
    void Decode();
    void Execute();

  private:
    // internal data representation
    std::unique_ptr<Z80> m_cpu;
    ZxMemory* m_memory;

    // instruction tables
    std::unique_ptr<instructions::NoPrefixTable> pTable;
    std::unique_ptr<instructions::CBTable> pCBTable;
};

} // namespace Trpp

#endif
