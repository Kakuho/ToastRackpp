#include "iomanager.hpp"
#include <memory>
#include <stdexcept>

namespace Trpp::IO{

using AddressType = std::uint16_t;

// ------------------------------------------------------ //
// Lifetime
// ------------------------------------------------------ //

IoManager::IoManager()
  :
    m_keyboard{std::make_unique<Keyboard>()}
{

}

// ------------------------------------------------------ //
// Port Read
// ------------------------------------------------------ //

[[nodiscard]] IoPort 
IoManager::Read(AddressType index) const{
  if(index % 2 == 0){
    return ReadFromKeyboard((index & 0xFF00) >> 8);
  }
  else{
    throw std::runtime_error{"Port is not even and not ULA"};
  }
}

[[nodiscard]] IoPort 
IoManager::ReadFromKeyboard(std::uint8_t index) const{
  switch(index){

    // these are the trivial ones

    case Keyboard::KB_B_SPACE:
      return m_keyboard->BSpace();

    case Keyboard::KB_H_ENTER:
      return m_keyboard->HEnter();

    case Keyboard::KB_Y_P:
      return m_keyboard->YP();

    case Keyboard::KB_6_0:
      return m_keyboard->Num2();

    case Keyboard::KB_1_5:
      return m_keyboard->Num1();

    case Keyboard::KB_Q_T:
      return m_keyboard->QT();

    case Keyboard::KB_A_G:
      return m_keyboard->AG();

    case Keyboard::KB_CAPS_V:
      return m_keyboard->CAPSV();

    // now we deal with the combinations of key presses

    default:
      throw std::runtime_error{"Combinations of keys are unimplemented"};
  }
}

} //namespace Trpp::IO
