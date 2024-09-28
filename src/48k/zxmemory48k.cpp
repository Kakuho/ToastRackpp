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

void ZxMemory48K::ScreenToPPM6V2() const{
  std::cout << "P6" << '\n'
            << "256 192 " << '\n' 
            << "255" << '\n';
  for(std::uint16_t x = 0; x < 256; x++){
    for(std::uint16_t y = 0; y < 192; y++){
      std::uint16_t address = CoordinateToAddress(x, y);
      if(m_buffer[address] == 0){
        for(int i = 0; i < 8; i++){
          std::cout << "0 0 0\n";
        }
      }
      else{

      }
    }
  }
}

std::uint16_t 
ZxMemory48K::AttributeAddress(std::uint16_t screenAddr) const{

}

} // namespace Trpp
