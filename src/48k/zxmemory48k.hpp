#ifndef ZXMEMORY48K_HPP
#define ZXMEMORY48K_HPP

// the 48k does not have any bank switching, this makes the memory system 
// of the 48k different from the memory system in 128k which incorporates bank switching.

#include <array>
#include <exception>
#include <cstdint>
#include <stdexcept>

#include "shared/zxmemory.hpp"

namespace trpp{

class ZxMemory48K final: public ZxMemory{
  public:
    ZxMemory48K() = default;
    ~ZxMemory48K() = default;

  private:
    std::array<std::uint8_t, ZxMemory::MEMORYSIZE> m_buffer;

  public:
    virtual const std::uint8_t& operator[](std::uint16_t addr) const noexcept override{
      return m_buffer[addr];
    }

    virtual std::uint8_t& operator[](std::uint16_t addr) noexcept override{
      return (*this)[addr];
    }

    virtual std::uint16_t ReadWord(std::uint16_t addr) const noexcept override{
      return ((*this)[addr+1] << 8) | (*this)[addr];
    }
};

} // namespace trpp

#endif
