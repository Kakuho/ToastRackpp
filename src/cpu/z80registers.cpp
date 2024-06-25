#include "z80registers.hpp"

namespace trpp{

Z80RegisterPair& Z80RegisterPair::operator=(Z80RegisterPair& src){ 
  *this = static_cast<std::uint16_t>(src);
  return *this;
}

Z80RegisterPair& Z80RegisterPair::operator=(std::uint16_t val){
  high =  ((val&0xFF00) >> 8);
  low =   (val&0xFF);
  return *this;
}

Z80RegisterPair& Z80RegisterPair::operator++(){
  std::uint16_t val = static_cast<std::uint16_t>(*this);
  val++;
  *this = val;
  return *this;
}

Z80RegisterPair Z80RegisterPair::operator++(int){
  Z80RegisterPair output = *this;
  std::uint16_t val = static_cast<std::uint16_t>(*this);
  val++;
  *this = val;
  return output;
}

Z80RegisterPair& Z80RegisterPair::operator--(){
  std::uint16_t val = static_cast<std::uint16_t>(*this);
  val--;
  *this = val;
  return *this;
}

Z80RegisterPair Z80RegisterPair::operator--(int){
  Z80RegisterPair output = *this;
  std::uint16_t val = static_cast<std::uint16_t>(*this);
  val--;
  *this = val;
  return output;
}

Z80Registers::Z80Registers():
  af1{}, 
  bc1{},
  de1{},
  hl1{},
  af2{},
  bc2{},
  de2{},
  hl2{},
  ir{},
  ix{0},
  iy{0},
  sp{0},
  pc{0}

{

}

Z80RegisterSet::Z80RegisterSet():
  af1{}, 
  bc1{},
  de1{},
  hl1{},
  af2{},
  bc2{},
  de2{},
  hl2{},
  ir{},
  ix{},
  iy{},
  sp{},
  pc{}
{

}

} // namespace trpp
