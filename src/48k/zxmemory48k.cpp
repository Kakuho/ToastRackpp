#include "zxmemory48k.hpp"

namespace Trpp{
// ------------------------------------------------------ //
//  Lifetime
// ------------------------------------------------------ //

ZxMemory48K::ZxMemory48K(){
  for(std::uint8_t& k : m_buffer){
    k = 0x00;
  }
};

ZxMemory48K::ZxMemory48K(std::initializer_list<std::uint8_t> src){
  std::size_t index = 0;
  for(auto i: src){
    m_buffer[index++] = i;
  }
}

// ------------------------------------------------------ //
//  For Debugging
// ------------------------------------------------------ //

void ZxMemory48K::Dump() const{
  std::size_t beg = 0;
  beg++;
  bool midbreak = false;
  std::cout << std::setw(8) << std::setfill('0') << beg-1
            << std::setw(3) << std::setfill(' ') << ' ';
  for(std::size_t i = beg; i < m_buffer.size(); i++){
    std::cout << std::hex << std::setw(2) << std::setfill('0')
              << std::bitset<8>(m_buffer[i - 1]).to_ulong();
    if((i % 16 == 0) && (i != 0)){
      std::cout << '\n';
      std::cout << std::setw(8) << std::setfill('0')
                << i << std::setw(3) << std::setfill(' ') << ' ';
      midbreak = false;
    }
    else if((i % 8 == 0 ) && (i != 0) && !midbreak){
      midbreak = true;
      std::cout << std::setw(4) << std::setfill(' ') << ' ' ;
    }
    else{
      std::cout << ' ';
    }
  }
  std::cout << '\n';
}

// ------------------------------------------------------ //
//  Screen debugging:
// ------------------------------------------------------ //

void ZxMemory48K::ScreenToPPM6V1() const{
  std::cout << "P6" << '\n'
            << "256 192 " << '\n' 
            << "255" << '\n';
  for(std::uint16_t i = 0x4000; i <= 0x57ff; i++){
    // get its attribute data
    if(i != 0){

    }
    else{
      for(std::uint8_t j = 0; j < 8; j++){
        std::cout << "0";
      }
    }
    if((i != 0x4000) && (i % 31 == 0)){
      // new line
    }
  }
}

// going wrong somewhere here...

inline std::uint16_t 
ZxMemory48K::CoordinateAddress(std::uint16_t x, std::uint16_t y) const
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

inline std::uint16_t
ZxMemory48K::AttributeAddress(std::uint16_t x, std::uint16_t y) const{ 
  // x is in bytes
  return 0x5800 + (((y/8) * 32) + x); 
}

using ColourType = std::uint64_t;

ColourType 
ZxMemory48K::GetInkColour(std::uint8_t attribute) const{
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
ZxMemory48K::GetPaperColour(std::uint8_t attribute) const{
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

std::pair<ColourType, ColourType>
ZxMemory48K::Colours(std::uint8_t attribute) const {
  return{
    GetInkColour(attribute),
    GetPaperColour(attribute)
  };
}

inline std::tuple<std::uint8_t, std::uint8_t, std::uint8_t>
ZxMemory48K::Decompose(ColourType colour) const{
  std::uint8_t red = colour >> 16;
  std::uint8_t green = (colour >> 8) & 0xFF;
  std::uint8_t blue = colour & 0xFF;
  return{
    red,
    green,
    blue
  };
}

void ZxMemory48K::ScreenToPPM6V2() const{
  std::cout << "P3" << '\n'
            << "256 192 " << '\n' 
            << "255" << '\n';
  for(std::uint16_t x = 0; x < 32; x++){
    for(std::uint16_t y = 0; y < 192; y++){
      auto [drawAddress, attributeAddress] = ScreenAddresses(x, y);
      std::uint8_t draw = m_buffer[drawAddress];
      std::uint8_t attribute = m_buffer[attributeAddress];
      auto [ink, paper] = Colours(attribute);
      // assuming no flashing
      for(int bitPos = 7; bitPos >= 0; bitPos--){
        bool on = draw & (1 << bitPos);
        if(on){
          // pixel is on - render ink pixel
          auto [r, g, b] = Decompose(ink);
          std::cout << std::dec
                    << (static_cast<unsigned>(r) & 0xFF) << ' '
                    << (static_cast<unsigned>(g) & 0xFF) << ' '
                    << (static_cast<unsigned>(b) & 0xFF) << '\n';
        }
        else{
          // pixel is off - render bg pixel
          auto [r, g, b] = Decompose(paper);
          std::cout << std::dec
                    << (static_cast<unsigned>(r) & 0xFF) << ' '
                    << (static_cast<unsigned>(g) & 0xFF) << ' '
                    << (static_cast<unsigned>(b) & 0xFF) << '\n';
        }
      }
    }
  }
}

} // namespace Trpp
