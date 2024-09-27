#ifndef IO_KEYBOARD_HPP  
#define IO_KEYBOARD_HPP

// ZX spectrum keyboard class
// https://worldofspectrum.org/ZXBasicManual/zxmanchap23.html

#include <array>
#include <cstdint>

#include "ioport.hpp"

namespace Trpp::IO{

class Keyboard{
  public:
    // Keyboard index constants

    static inline constexpr std::uint8_t KB_B_SPACE = 0x7F;
    static inline constexpr std::uint8_t KB_H_ENTER = 0xBF;
    static inline constexpr std::uint8_t KB_Y_P     = 0xDF;
    static inline constexpr std::uint8_t KB_6_0     = 0xEF;
    static inline constexpr std::uint8_t KB_1_5     = 0xF7;
    static inline constexpr std::uint8_t KB_Q_T     = 0xFB;
    static inline constexpr std::uint8_t KB_A_G     = 0xFD;
    static inline constexpr std::uint8_t KB_CAPS_V  = 0xFE;

    // ------------------------------------------------------ //
    //  Hooks to the underlying ioports
    // ------------------------------------------------------ //

    const IoPort& BSpace()  const { return m_ports[0];}
    const IoPort& HEnter()  const { return m_ports[1];}
    const IoPort& YP()      const { return m_ports[2];}
    const IoPort& Num2()    const { return m_ports[3];}
    const IoPort& Num1()    const { return m_ports[4];}
    const IoPort& QT()      const { return m_ports[5];}
    const IoPort& AG()      const { return m_ports[6];}
    const IoPort& CAPSV()   const { return m_ports[7];}

    IoPort& BSpace()  { return m_ports[0];}
    IoPort& HEnter()  { return m_ports[1];}
    IoPort& YP()      { return m_ports[2];}
    IoPort& Num2()    { return m_ports[3];}
    IoPort& Num1()    { return m_ports[4];}
    IoPort& QT()      { return m_ports[5];}
    IoPort& AG()      { return m_ports[6];}
    IoPort& CAPSV()   { return m_ports[7];}

  public:
    // ------------------------------------------------------ //
    // Toggles
    // ------------------------------------------------------ //

    // Reference: http://slady.net/Sinclair-ZX-Spectrum-keyboard/layout/

    enum class KeyPosition: std::uint8_t{
      Zero = 0, One = 1, Two = 2, Three = 3, Four = 4
    };

    void ToggleKey(IoPort& port, KeyPosition pos);

    // Bottom Row - [ Shift - V ] [ B - Space ]
    
    void ToggleCapShift() { ToggleKey( CAPSV(), KeyPosition::Zero); }
    void ToggleZ()        { ToggleKey( CAPSV(), KeyPosition::One); }
    void ToggleX()        { ToggleKey( CAPSV(), KeyPosition::Two); }
    void ToggleC()        { ToggleKey( CAPSV(), KeyPosition::Three); }
    void ToggleV()        { ToggleKey( CAPSV(), KeyPosition::Four); }

    void ToggleB()        { ToggleKey( BSpace(), KeyPosition::Four); }
    void ToggleN()        { ToggleKey( BSpace(), KeyPosition::Three); }
    void ToggleM()        { ToggleKey( BSpace(), KeyPosition::Two); }
    void ToggleSymShift() { ToggleKey( BSpace(), KeyPosition::One); }
    void ToggleSpace()    { ToggleKey( BSpace(), KeyPosition::Zero); }

    // Second Row - [ A - G ] [ H - Enter ]

    void ToggleA()        { ToggleKey( AG(), KeyPosition::Zero); }
    void ToggleS()        { ToggleKey( AG(), KeyPosition::One); }
    void ToggleD()        { ToggleKey( AG(), KeyPosition::Two); }
    void ToggleF()        { ToggleKey( AG(), KeyPosition::Three); }
    void ToggleG()        { ToggleKey( AG(), KeyPosition::Four); }

    void ToggleH()        { ToggleKey( HEnter(), KeyPosition::Four); }
    void ToggleJ()        { ToggleKey( HEnter(), KeyPosition::Three); }
    void ToggleK()        { ToggleKey( HEnter(), KeyPosition::Two); }
    void ToggleL()        { ToggleKey( HEnter(), KeyPosition::One); }
    void ToggleEnter()    { ToggleKey( HEnter(), KeyPosition::Zero); }

    // Third Row - [ Q - T ] [ Y - P ]
    void ToggleQ()        { ToggleKey( QT(), KeyPosition::Zero); }
    void ToggleW()        { ToggleKey( QT(), KeyPosition::One); }
    void ToggleE()        { ToggleKey( QT(), KeyPosition::Two); }
    void ToggleR()        { ToggleKey( QT(), KeyPosition::Three); }
    void ToggleT()        { ToggleKey( QT(), KeyPosition::Four); }

    void ToggleY()        { ToggleKey( YP(), KeyPosition::Four); }
    void ToggleU()        { ToggleKey( YP(), KeyPosition::Three); }
    void ToggleI()        { ToggleKey( YP(), KeyPosition::Two); }
    void ToggleO()        { ToggleKey( YP(), KeyPosition::One); }
    void ToggleP()        { ToggleKey( YP(), KeyPosition::Zero); }

    // Top Row - [ 1 - 5 ] [ 6 - 0 ]

    void Toggle1()        { ToggleKey( Num1(), KeyPosition::Zero); }
    void Toggle2()        { ToggleKey( Num1(), KeyPosition::One); }
    void Toggle3()        { ToggleKey( Num1(), KeyPosition::Two); }
    void Toggle4()        { ToggleKey( Num1(), KeyPosition::Three); }
    void Toggle5()        { ToggleKey( Num1(), KeyPosition::Four); }

    void Toggle6()        { ToggleKey( Num2(), KeyPosition::Four); }
    void Toggle7()        { ToggleKey( Num2(), KeyPosition::Three); }
    void Toggle8()        { ToggleKey( Num2(), KeyPosition::Two); }
    void Toggle9()        { ToggleKey( Num2(), KeyPosition::One); }
    void Toggle0()        { ToggleKey( Num2(), KeyPosition::Zero); }

  private:
    std::array<IoPort, 8> m_ports;
};

} // namespace Trpp::IO

#endif
