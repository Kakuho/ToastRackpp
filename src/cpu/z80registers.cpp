#include "z80registers.hpp"

namespace trpp{

Z80RegisterPair& Z80RegisterPair::operator=(std::uint16_t val){
  high =  (val&0xFF00) >> 8;
  low =   (val&0xFF) >> 8;
  return *this;
}

Z80RegisterPair& Z80RegisterPair::operator=(Z80RegisterPair& src){ 
  *this = static_cast<std::uint16_t>(src);
  return *this;
}

}
