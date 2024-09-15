#ifndef CPU_Z80BRIDGE_HPP 
#define CPU_Z80BRIDGE_HPP

// Class to represent the driving class of a z80 cpu and 
// connections to the other emulated systems
//
// the cpu core functionalities is within class Z80

#include <memory>

#include "z80.hpp"
#include "shared/zxmemory.hpp"

namespace trpp{

class Z80Bridge{
  public:
    //-------------------------------------------------------------
    //  Lifetime
    //-------------------------------------------------------------

    Z80Bridge(ZxMemory* memory);

    //-------------------------------------------------------------
    //  Cpu Driving Functions
    //-------------------------------------------------------------

    void Tick();
    void TickCBPrefix();
    void TickNoPrefix();


    //-------------------------------------------------------------
    //  
    //-------------------------------------------------------------

  private:
    // internal data representation
    std::unique_ptr<Z80> m_cpu;
    ZxMemory* m_memory;
};

} // namespace Trpp

#endif
