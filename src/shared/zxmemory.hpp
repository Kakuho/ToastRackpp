#ifndef ZXMEMORY_HPP
#define ZXMEMORY_HPP

// provides a shared interface for 48k and 128k memory systems via 
// runtime dispatching

#include <array>
#include <exception>
#include <cstdint>
#include <stdexcept>

namespace trpp{

class ZxMemory{
  public:
    ZxMemory() = default;
    ~ZxMemory() = default;
    virtual std::uint8_t& operator[](std::uint16_t addr) noexcept= 0;
    virtual const std::uint8_t& operator[](std::uint16_t addr) const noexcept= 0;
    virtual std::uint16_t ReadWord(std::uint16_t addr) const noexcept = 0;

  protected:
    static constexpr std::size_t MEMORYSIZE = 65536;
};

} // namespace trpp

#endif
