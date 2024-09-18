#include "zxmemory48k.hpp"

namespace trpp{
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

}
