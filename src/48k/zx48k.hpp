#ifndef ZX48K_HPP
#define ZX48K_HPP

// class to encapuslates the ZX Spectrum 48K

#include <memory>

#include "cpu/z80.hpp"
#include "zxmemory48k.hpp"

namespace trpp{

class Zx48k{
  public:
    Zx48k(): 
      m_z80{std::make_unique<Z80>()},
      m_memory{std::make_unique<ZxMemory48K>()}
    {
      m_z80->ConnectMemory(m_memory.get());
    }

  private:
    std::unique_ptr<Z80> m_z80;
    std::unique_ptr<ZxMemory48K> m_memory;
};

}

#endif
