#ifndef ZX48K_HPP
#define ZX48K_HPP

// Class to encapuslates the ZX Spectrum 48K system as a whole

#include <memory>
#include <string>
#include <stdexcept>

#include "zxmemory48k.hpp"
#include "cpu/z80.hpp"
#include "cpu/z80bridge.hpp"
#include "loader/utils.hpp"
#include "loader/z80loader/z80loader.hpp"

namespace Trpp{

class Spectrum48K{
  public:
    // ------------------------------------------------------ //
    // Lifetime
    // ------------------------------------------------------ //

    explicit Spectrum48K();
    
    //-------------------------------------------------------------
    //  File Loading Routines
    //-------------------------------------------------------------

    void LoadROM(std::string&& filename);
    void LoadFile(std::string&& filename);

  private:
    void LoadZ80();
    void LoadTap();

    // ------------------------------------------------------ //
    //  Driving code
    // ------------------------------------------------------ //

    void Run();

  private:
    std::unique_ptr<ZxMemory48K> m_memory;
    std::unique_ptr<CPU::Z80Bridge> m_cpuBridge;
    std::string m_filename;
};

} // namespace Trpp

#endif
