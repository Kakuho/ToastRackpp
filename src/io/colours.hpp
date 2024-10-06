#ifndef IO_COLOURS_HPP 
#define IO_COLOURS_HPP 
// constants for the colour pallete

#include <cstdint>

namespace Trpp::IO{
  // note the colours are all 48 bit long, 
  // I use 64 bit integers to represent them
  inline constexpr std::uint64_t BLACK    = 0x00'000000;
  inline constexpr std::uint64_t BLUE     = 0x00'0100CE;
  inline constexpr std::uint64_t RED      = 0x00'CF0100;
  inline constexpr std::uint64_t MAGENTA  = 0x00'CF01CE;
  inline constexpr std::uint64_t GREEN    = 0x00'00CF15;
  inline constexpr std::uint64_t CYAN     = 0x00'01CFCF;
  inline constexpr std::uint64_t YELLOW   = 0x00'CFCF15;
  inline constexpr std::uint64_t WHITE    = 0x00'CFCFCF;
  // bright variation
  inline constexpr std::uint64_t BRIGHT_BLACK    = 0x00'000000;
  inline constexpr std::uint64_t BRIGHT_BLUE     = 0x00'0200FD;
  inline constexpr std::uint64_t BRIGHT_RED      = 0x00'FF0201;
  inline constexpr std::uint64_t BRIGHT_MAGENTA  = 0x00'FF02FD;
  inline constexpr std::uint64_t BRIGHT_GREEN    = 0x00'00FF1C;
  inline constexpr std::uint64_t BRIGHT_CYAN     = 0x00'02FFFF;
  inline constexpr std::uint64_t BRIGHT_YELLOW   = 0x00'FFFF1D;
  inline constexpr std::uint64_t BRIGHT_WHITE    = 0x00'FFFFFF;
} // namespace Trpp::IO

#endif
