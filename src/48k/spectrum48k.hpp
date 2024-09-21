#ifndef ZX48K_HPP
#define ZX48K_HPP

// Class to encapuslates the ZX Spectrum 48K system as a whole

#include <memory>
#include <string>

#include "cpu/z80.hpp"
#include "cpu/z80bridge.hpp"
#include "zxmemory48k.hpp"

namespace trpp{

class Spectrum48K{
  public:
    // ------------------------------------------------------ //
    // Lifetime
    // ------------------------------------------------------ //
    explicit Spectrum48K();
    
    //-------------------------------------------------------------
    // Operational
    //-------------------------------------------------------------

    void ReadFile(std::string&& filename);

    // ------------------------------------------------------ //
    //  Driving code
    // ------------------------------------------------------ //
    void Run();

  private:
    std::unique_ptr<ZxMemory48K> m_memory;
    std::unique_ptr<Z80Bridge> m_cpuBridge;
};

} // namespace trpp

#endif
