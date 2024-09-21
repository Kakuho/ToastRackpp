#include "spectrum48k.hpp"
#include <memory>

namespace trpp{

// ------------------------------------------------------ //
//  Lifetime
// ------------------------------------------------------ //

Spectrum48K::Spectrum48K()
  :
    m_memory{std::make_unique<ZxMemory48K>()},
    m_cpuBridge{std::make_unique<Z80Bridge>(m_memory.get())}
{
}

// ------------------------------------------------------ //
//  Driving code
// ------------------------------------------------------ //

void Spectrum48K::Run(){
  m_cpuBridge->Step();
  m_cpuBridge->TriggerNmi();
  m_cpuBridge->Step();
}

} // namespace trpp
