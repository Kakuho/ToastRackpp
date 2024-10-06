#include "vram_utils.hpp"

namespace Trpp{

using ColourType = std::uint64_t;
using AddressType = std::uint16_t;

AddressType
CoordinateAddress(std::uint16_t x, std::uint16_t y)
{
  // x is in bytes
  std::uint16_t coordinate = 0b010 << 2;
  coordinate |= ((y & 0xc0) >> 6);
  coordinate <<= 3;
  coordinate |= (y & 0x7);
  coordinate <<= 3;
  coordinate |= ((y & 0x38) >> 3);
  coordinate <<= 5;
  coordinate |= x & 0x1F;
  return coordinate;
}

AddressType
AttributeAddress(std::uint16_t x, std::uint16_t y){ 
  // x is in bytes
  return 0x5800 + (((y/8) * 32) + x); 
}

ColourType 
GetInkColour(std::uint8_t attribute){
  std::uint8_t inkIndex = attribute & 0x7;
  bool bright = attribute & 0x40;
  switch (inkIndex){
    case 0:
      return bright ? IO::BRIGHT_BLACK : IO::BLACK;
    case 1:
      return bright ? IO::BRIGHT_BLUE : IO::BLUE;
    case 2:
      return bright ? IO::BRIGHT_RED : IO::RED;
    case 3:
      return bright ? IO::BRIGHT_MAGENTA : IO::MAGENTA;
    case 4:
      return bright ? IO::BRIGHT_GREEN : IO::GREEN;
    case 5:
      return bright ? IO::BRIGHT_CYAN : IO::CYAN;
    case 6:
      return bright ? IO::BRIGHT_YELLOW : IO::YELLOW;
    case 7:
      return bright ? IO::BRIGHT_WHITE : IO::WHITE;
    default:
      return bright ? IO::BRIGHT_YELLOW : IO::YELLOW;
  }
}

ColourType 
GetPaperColour(std::uint8_t attribute){
  std::uint8_t paperIndex = (attribute & 0x38) >> 3;
  bool bright = attribute & 0x40;
  switch (paperIndex){
    case 0:
      return bright ? IO::BRIGHT_BLACK : IO::BLACK;
    case 1:
      return bright ? IO::BRIGHT_BLUE : IO::BLUE;
    case 2:
      return bright ? IO::BRIGHT_RED : IO::RED;
    case 3:
      return bright ? IO::BRIGHT_MAGENTA : IO::MAGENTA;
    case 4:
      return bright ? IO::BRIGHT_GREEN : IO::GREEN;
    case 5:
      return bright ? IO::BRIGHT_CYAN : IO::CYAN;
    case 6:
      return bright ? IO::BRIGHT_YELLOW : IO::YELLOW;
    case 7:
      return bright ? IO::BRIGHT_WHITE : IO::WHITE;
    default:
      return bright ? IO::BRIGHT_YELLOW : IO::YELLOW;
  }
}

std::pair<AddressType, AddressType>
ScreenAddresses(std::uint16_t x, std::uint16_t y){
  return {
    CoordinateAddress(x, y),
    AttributeAddress(x, y)
  };
}

std::pair<ColourType, ColourType>
Colours(std::uint8_t attribute){
  return{
    GetInkColour(attribute),
    GetPaperColour(attribute)
  };
}

std::tuple<std::uint8_t, std::uint8_t, std::uint8_t>
Rgb(ColourType colour){
  std::uint8_t red = colour >> 16;
  std::uint8_t green = (colour >> 8) & 0xFF;
  std::uint8_t blue = colour & 0xFF;
  return{
    red,
    green,
    blue
  };
}

} // namespace Trpp
