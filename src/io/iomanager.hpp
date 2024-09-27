#ifndef IO_IOMANAGER_HPP
#define IO_IOMANAGER_HPP

// class to represent the interface between the Z80 cpu and the 
// io peripherals

#include <unordered_map>
#include <cstdint>
#include <cassert>
#include <stdexcept>
#include <memory>

#include "ioport.hpp"
#include "keyboard.hpp"

namespace Trpp::IO{

class IoManager{
  using AddressType = std::uint16_t;
  public:
    // ------------------------------------------------------ //
    // Lifetime
    // ------------------------------------------------------ //

    IoManager();

  public:

    // ------------------------------------------------------ //
    // Port Read 
    // ------------------------------------------------------ //

    [[nodiscard]] IoPort 
    Read(AddressType index) const;

    [[nodiscard]] IoPort 
    ReadFromKeyboard(std::uint8_t index) const;

    // ------------------------------------------------------ //
    // Port Write
    // ------------------------------------------------------ //

    void Write(AddressType index) noexcept;

  private:
    std::unique_ptr<Keyboard> m_keyboard;
};

} //namespace Trpp::Io

#endif
