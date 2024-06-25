#ifndef DEBUGZ80_HPP
#define DEBUGZ80_HPP

#include "z80.hpp"

namespace trpp{

class DebugZ80 final: public Z80{
  // the debug class has access to all the state of the processor, and 
  // provides handlers to every internal instruction
  public:
    explicit DebugZ80() = default;
    virtual ~DebugZ80() override = default;

  private:
    CpuLogger logger;
  
  public:
    bool RegistersAllZero(){
      return 
        // first set
        m_regs.af1 == 0 && m_regs.bc1 == 0 && m_regs.de1 == 0
        && m_regs.hl1 ==0 &&
        // second set
        m_regs.af2 == 0 && m_regs.bc2 == 0 && m_regs.de2 == 0
        && m_regs.hl2 == 0
        // special regs
        && m_regs.ir == 0 && m_regs.ix == 0 && m_regs.iy == 0
        && m_regs.sp == 0 && m_regs.pc == 0;
    }

    std::uint8_t& registerTable(std::uint8_t r){
      return Z80::registerTable(r);
    }
    Z80RegisterPair& registerPairSPTable(std::uint8_t r){ 
      return Z80::registerPairSPTable(r); 
    }
    Z80RegisterPair& registerPairAFTable(std::uint8_t r){
      return Z80::registerPairAFTable(r); 
    }

  public:
    // handlers
    // first set
    std::uint8_t GetA1(){return m_regs.a1;}
    void SetA1(std::uint8_t val){ m_regs.a1 = val; }

    std::uint8_t GetF1(){return m_regs.f1;}
    void SetF1(std::uint8_t val){ m_regs.f1 = val; }

    std::uint8_t GetB1(){return m_regs.b1;}
    void SetB1(std::uint8_t val){ m_regs.b1 = val; }

    std::uint8_t GetC1(){return m_regs.c1;}
    void SetC1(std::uint8_t val){ m_regs.c1 = val; }

    std::uint8_t GetD1(){return m_regs.d1;}
    void SetD1(std::uint8_t val){ m_regs.d1 = val; }

    std::uint8_t GetE1(){return m_regs.e1;}
    void SetE1(std::uint8_t val){ m_regs.e1 = val; }

    std::uint8_t GetH1(){return m_regs.h1;}
    void SetH1(std::uint8_t val){ m_regs.h1 = val; }

    std::uint8_t GetL1(){return m_regs.l1;}
    void SetL1(std::uint8_t val){ m_regs.l1 = val; }

    // second set
    std::uint8_t GetA2(){return m_regs.a2;}
    void SetA2(std::uint8_t val){ m_regs.a2 = val; }

    std::uint8_t GetF2(){return m_regs.f2;}
    void SetF2(std::uint8_t val){ m_regs.f2 = val; }

    // pairs of registers
    // first set
    std::uint16_t GetAF1(){ return m_regs.af1;}
    std::uint16_t GetBC1(){ return m_regs.bc1;}
    std::uint16_t GetDE1(){ return m_regs.de1;}
    std::uint16_t GetHL1(){ return m_regs.hl1;}
    std::uint16_t GetSP(){ return m_regs.sp;}

    // second set
    std::uint16_t GetAF2(){ return m_regs.af2;}
};

} // namespace trpp

#endif
