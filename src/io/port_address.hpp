#ifndef IO_PORT_ADDRESSES_HPP
#define IO_PORT_ADDRESSES_HPP

// Constants for io ports

#include <cstdint>

namespace Trpp::IO{
  // keyboard ports
  inline constexpr std::uint16_t KB_B_SPACE = 0x7FFE;
  inline constexpr std::uint16_t KB_H_ENTER = 0xBFFE;
  inline constexpr std::uint16_t KB_Y_P     = 0xDFFE;
  inline constexpr std::uint16_t KB_6_0     = 0xEFFE;
  inline constexpr std::uint16_t KB_1_5     = 0xF7FE;
  inline constexpr std::uint16_t KB_Q_T     = 0xFBFE;
  inline constexpr std::uint16_t KB_A_G     = 0xFDFE;
  inline constexpr std::uint16_t KB_CAPS_V  = 0xFEFE;
}

#endif
