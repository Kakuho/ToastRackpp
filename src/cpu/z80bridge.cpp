#include "z80bridge.hpp"
#include <memory>

namespace trpp{
//-------------------------------------------------------------
//  Lifetime 
//-------------------------------------------------------------

Z80Bridge::Z80Bridge(ZxMemory* memory)
  :
    m_cpu{std::make_unique(Z80)},
    m_memory{memory}
{
  m_cpu->ConnectMemory(m_memory);
}

//-------------------------------------------------------------
// Cpu Driving Functions
//-------------------------------------------------------------

void Z80Bridge::Tick(){

}

}
