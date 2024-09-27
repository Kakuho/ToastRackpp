#include "keyboard.hpp"

namespace Trpp::IO{

// 0b010 -> 0b000

void Keyboard::ToggleKey(IoPort& port, KeyPosition pos){
  std::uint8_t shiftAmount = static_cast<std::uint8_t>(pos);
  if(port.value & (1 << shiftAmount)){
    port.value &= (1 << shiftAmount);
  }
  else{
    port.value |= (1 << shiftAmount);
  }
}

} // namespace Trpp::IO
