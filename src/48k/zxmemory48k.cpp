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

void ZxMemory48K::ScreenToPPM6() const{
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
          auto [r, g, b] = Rgb(ink);
          std::cout << std::dec
                    << (static_cast<unsigned>(r) & 0xFF) << ' '
                    << (static_cast<unsigned>(g) & 0xFF) << ' '
                    << (static_cast<unsigned>(b) & 0xFF) << '\n';
        }
        else{
          // pixel is off - render bg pixel
          auto [r, g, b] = Rgb(paper);
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
