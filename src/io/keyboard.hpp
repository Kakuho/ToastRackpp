// zx spectrum keyboard class
// https://worldofspectrum.org/ZXBasicManual/zxmanchap23.html

#include <array>
#include "ioport.hpp"

namespace trpp{

class Keyboard{
  public:

    // Hooks to the underlying ioports

    IoPort& BSpace();
    IoPort& HEnter();
    IoPort& YP();
    IoPort& Num2();
    IoPort& Num1();
    IoPort& QT();
    IoPort& AG();
    IoPort& CAPSV();

  private:
    std::array<IoPort, 8> m_ports;
};

} // namespace trpp
