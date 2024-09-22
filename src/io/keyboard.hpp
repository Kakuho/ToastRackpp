// zx spectrum keyboard class
// https://worldofspectrum.org/ZXBasicManual/zxmanchap23.html

#include <array>
#include "ioport.hpp"

namespace Trpp::IO{

class Keyboard{
  public:

    // ------------------------------------------------------ //
    //  Hooks to the underlying ioports
    // ------------------------------------------------------ //

    IoPort& BSpace()  { return m_ports[0];}
    IoPort& HEnter()  { return m_ports[1];}
    IoPort& YP()      { return m_ports[2];}
    IoPort& Num2()    { return m_ports[3];}
    IoPort& Num1()    { return m_ports[4];}
    IoPort& QT()      { return m_ports[5];}
    IoPort& AG()      { return m_ports[6];}
    IoPort& CAPSV()   { return m_ports[7];}

    // ------------------------------------------------------ //
    //  Keyboard Functionality
    // ------------------------------------------------------ //

  private:
    std::array<IoPort, 8> m_ports;
};

} // namespace Trpp::IO
