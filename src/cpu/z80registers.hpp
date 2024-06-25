#ifndef Z80REGISTERS_HPP
#define Z80REGISTERS_HPP

#include <cstdint>

namespace trpp{

struct Z80RegisterPair{
  public: 
    constexpr Z80RegisterPair(): high{0}, low{0}{}
    constexpr Z80RegisterPair(Z80RegisterPair& src): high{src.high}, low{src.low}{}
    Z80RegisterPair& operator=(Z80RegisterPair& src);
    Z80RegisterPair& operator=(std::uint16_t val);
    // arithmetic operator overloads
    Z80RegisterPair& operator++();
    Z80RegisterPair operator++(int);
    Z80RegisterPair& operator--();
    Z80RegisterPair operator--(int);
    // bitwise operator overloads
    constexpr operator std::uint16_t(){ 
      return (static_cast<std::uint16_t>(high) << 8) | low;
    }

  public:
    std::uint8_t high;
    std::uint8_t low;
};

struct Z80Registers{
  public:
    Z80Registers();

    // first set
    Z80RegisterPair af1;
    Z80RegisterPair bc1;
    Z80RegisterPair de1;
    Z80RegisterPair hl1;

    // second set
    Z80RegisterPair af2;
    Z80RegisterPair bc2;
    Z80RegisterPair de2;
    Z80RegisterPair hl2;

    // special purpose registers
    Z80RegisterPair ir;
    std::uint16_t ix;
    std::uint16_t iy;
    std::uint16_t sp;
    std::uint16_t pc;

    std::uint8_t& i = ir.high;
    std::uint8_t& r = ir.low;

    // first set of 8 bit individual registers
    std::uint8_t& a1 = af1.high;
    std::uint8_t& f1 = af1.low;
    std::uint8_t& b1 = bc1.high; 
    std::uint8_t& c1 = bc1.low; 
    std::uint8_t& d1 = de1.high; 
    std::uint8_t& e1 = de1.low; 
    std::uint8_t& h1 = hl1.high; 
    std::uint8_t& l1 = hl1.low; 

    // second set of 8 bit individual registers
    std::uint8_t& a2 = af2.high;
    std::uint8_t& f2 = af2.low;
    std::uint8_t& b2 = bc2.high; 
    std::uint8_t& c2 = bc2.low; 
    std::uint8_t& d2 = de2.high; 
    std::uint8_t& e2 = de2.low; 
    std::uint8_t& h2 = hl2.high; 
    std::uint8_t& l2 = hl2.low; 
};

struct Z80RegisterSet{
  using Z80Register = Z80RegisterPair;
  public:

    Z80RegisterSet();

    // first set
    Z80Register af1;
    Z80Register bc1;
    Z80Register de1;
    Z80Register hl1;

    // second set
    Z80Register af2;
    Z80Register bc2;
    Z80Register de2;
    Z80Register hl2;

    // special purpose registers
    Z80Register ir;
    Z80Register ix;
    Z80Register iy;
    Z80Register sp;
    Z80Register pc;

    std::uint8_t& i = ir.high;
    std::uint8_t& r = ir.low;

    // first set of 8 bit individual registers
    std::uint8_t& a1 = af1.high;
    std::uint8_t& f1 = af1.low;
    std::uint8_t& b1 = bc1.high; 
    std::uint8_t& c1 = bc1.low; 
    std::uint8_t& d1 = de1.high; 
    std::uint8_t& e1 = de1.low; 
    std::uint8_t& h1 = hl1.high; 
    std::uint8_t& l1 = hl1.low; 

    // second set of 8 bit individual registers
    std::uint8_t& a2 = af2.high;
    std::uint8_t& f2 = af2.low;
    std::uint8_t& b2 = bc2.high; 
    std::uint8_t& c2 = bc2.low; 
    std::uint8_t& d2 = de2.high; 
    std::uint8_t& e2 = de2.low; 
    std::uint8_t& h2 = hl2.high; 
    std::uint8_t& l2 = hl2.low; 
};

struct Z80State{

};

}

#endif
