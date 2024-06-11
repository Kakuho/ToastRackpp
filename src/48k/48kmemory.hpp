#ifndef MEMORY_48K_HPP
#define MEMORY_48K_HPP

// the 48k does not have any bank switching, this makes the memory system 
// of the 48k different from the memory system in 128k which incorporates bank switching.

#include <array>
#include <exception>
#include <cstdint>
#include <stdexcept>

namespace trpp{

  class ZxMemory{
    // provides a shared interface for 48k and 128k memory systems
    public:
      ZxMemory() = default;
      ~ZxMemory() = default;
      virtual std::uint8_t& operator[](std::uint16_t addr) noexcept= 0;
      virtual const std::uint8_t& operator[](std::uint16_t addr) const noexcept= 0;
      virtual std::uint16_t ReadWord(std::uint16_t addr) const noexcept = 0;

    protected:
      static constexpr std::size_t MEMORYSIZE = 65536;
  };

  class Memory48K final: public ZxMemory{
    public:
      Memory48K() = default;
      ~Memory48K() = default;

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
}

#endif
