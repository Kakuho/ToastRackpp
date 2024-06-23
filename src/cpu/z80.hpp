#ifndef Z80_HPP
#define Z80_HPP

#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "z80registers.hpp"
#include "cpulogger.hpp"

namespace trpp{

class Z80{
  public:
    explicit Z80() = default;
    virtual ~Z80() = default;

    void Fetch();
    void Decode();
    void Execute();
    constexpr std::uint16_t formWord(std::uint8_t high, std::uint8_t low) const{
      return (static_cast<std::uint16_t>(high) << 8) | low;
    }

  protected:
    Z80Registers m_regs;

  public:

    std::uint8_t& registerTable(std::uint8_t r){
      switch(r){
        case 0b000:
          return m_regs.b1;
        case 0b001:
          return m_regs.c1;
        case 0b010:
          return m_regs.d1;
        case 0b011:
          return m_regs.e1;
        case 0b100:
          return m_regs.h1;
        case 0b101:
          return m_regs.l1;
        case 0b110:
          throw std::runtime_error{"unable to decode register r = 0b110"};
        case 0b111:
          return m_regs.a1;
        default:
          throw std::runtime_error{"unable to decode register r = 0b110"};
      }
    }

    //---------------------------------------------------------------//
    // No PREFIX
    //---------------------------------------------------------------//

    void NOP(){}
    void EX_AF_AF2();
    void LD_dd_nn(std::uint8_t dd, std::uint8_t n1, std::uint8_t n2);
    void LD_r_r(std::uint8_t r, std::uint8_t rp);
    void LD_r_n(std::uint8_t r, std::uint8_t n);
    //void LD_r_hl(std::uint8_t r);
    //void LD_hl_r(std::uint8_t r);
    //void LD_hl_n(std::uint8_t n);

    //---------------------------------------------------------------//
    // DD PREFIX
    //---------------------------------------------------------------//

    //void LD_r_ixd(std::uint8_t r, std::uint8_t d);
    //void LD_ixd_r(std::uint8_t d, std::uint8_t r);

    //---------------------------------------------------------------//
    // FD PREFIX
    //---------------------------------------------------------------//

    //void LD_r_iyd(std::uint8_t r, std::uint8_t d);
    //void LD_iyd_r(std::uint8_t d, std::uint8_t r);
};

class DebugZ80: public Z80{
  // the debug class has access to all the state of the processor
  public:
    explicit DebugZ80() = default;
    virtual ~DebugZ80() override = default;

  private:
    CpuLogger logger;

  public:
    std::uint8_t GetA1(){return m_regs.a1;}
    void SetA1(std::uint8_t val){ m_regs.a1 = val; }
    std::uint8_t GetF1(){return m_regs.f1;}
    void SetF1(std::uint8_t val){ m_regs.f1 = val; }
    std::uint8_t GetA2(){return m_regs.a2;}
    void SetA2(std::uint8_t val){ m_regs.a2 = val; }
    std::uint8_t GetF2(){return m_regs.f2;}
    void SetF2(std::uint8_t val){ m_regs.f2 = val; }

    // pairs of registers
    std::uint16_t GetAF1(){ return m_regs.af1;}
    std::uint16_t GetAF2(){ return m_regs.af2;}

    struct InstructionParams{
      std::uint8_t dd;
      std::uint8_t n1;
      std::uint8_t n2;
    };

  public:
    //---------------------------------------------------------------//
    // No PREFIX
    //---------------------------------------------------------------//

    void EX_AF_AF2();
    void LD_dd_nn(std::uint8_t dd, std::uint8_t n1, std::uint8_t n2);

};

} // namespace trpp

#endif
