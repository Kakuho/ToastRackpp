#ifndef ZXMEMORY48K_HPP
#define ZXMEMORY48K_HPP

// the 48k does not have any bank switching, this makes the memory system 
// of the 48k different from the memory system in 128k, which 
// incorporates bank switching.

#include <array>
#include <exception>
#include <cstdint>
#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <bitset>

#include "shared/zxmemory.hpp"

namespace Trpp{

class ZxMemory48K final: public ZxMemory{
  public:
    // ------------------------------------------------------ //
    //  Lifetime
    // ------------------------------------------------------ //

    ZxMemory48K();
    ZxMemory48K(std::initializer_list<std::uint8_t> src);
    ~ZxMemory48K() = default;

    // ------------------------------------------------------ //
    //  For Debugging
    // ------------------------------------------------------ //

    void Dump() const;
    void DumpScreen() const;

    // ------------------------------------------------------ //
    //  Screen debugging
    // ------------------------------------------------------ //

    void ScreenToPPM6V1() const;
    void ScreenToPPM6V2() const;
    std::uint16_t 
    CoordinateToAddress(std::uint16_t x, std::uint16_t y) const;

    std::uint16_t 
    AttributeAddress(std::uint16_t screenAddr) const;


    // ------------------------------------------------------ //
    //  Operator Overloads
    // ------------------------------------------------------ //

    virtual const std::uint8_t& 
    operator[](std::uint16_t addr) const noexcept override{
      return m_buffer[addr];
    }

    virtual std::uint8_t& 
    operator[](std::uint16_t addr) noexcept override{
      return m_buffer[addr];
    }

    virtual std::uint16_t 
    ReadWord(std::uint16_t addr) const noexcept override{
      return ((*this)[addr+1] << 8) | (*this)[addr];
    }

  private:
    // the backing data is just a array
    std::array<std::uint8_t, ZxMemory::MEMORYSIZE> m_buffer;
};

} // namespace Trpp

#endif
