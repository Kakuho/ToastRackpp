#ifndef Z80_HPP
#define Z80_HPP

#include <cstdint>
#include <iostream>
#include <stdexcept>

#include "z80registers.hpp"
#include "cpulogger.hpp"
#include "shared/zxmemory.hpp"

namespace trpp{

class Z80{
  public:
    explicit Z80() = default;
    virtual ~Z80() = default;
    void ConnectMemory(ZxMemory* memory){ m_memory = memory;}

    // standard operational functions
    void Fetch();
    void Decode();
    void Execute();

  protected:
    Z80Registers m_regs;
    ZxMemory* m_memory; 

  public:
    // memory addressing functions
    constexpr std::uint16_t formWord(std::uint8_t high, std::uint8_t low) const{
      return (static_cast<std::uint16_t>(high) << 8) | low;
    }

    // stack functions
    void PushByte(std::uint8_t byte);

  public:
    // instruction operand tables:
    std::uint8_t& registerTable(std::uint8_t r);
    Z80RegisterPair& registerPairRPTable(std::uint8_t r); // we probably need a 
                                                          // union for this
    Z80RegisterPair& registerPairAFTable(std::uint8_t r); // we probably need a 
                                                          // union for this
  public:

    //---------------------------------------------------------------//
    // INSTRUCTIONS
    //---------------------------------------------------------------//
    // NO PREFIX - 8-bit Loads
    //---------------------------------------------------------------//

    void NOP(){}
    void LD_r_r(std::uint8_t r, std::uint8_t rp);
    void LD_r_n(std::uint8_t r, std::uint8_t n);
    void LD_r_hl(std::uint8_t r);
    void LD_hl_r(std::uint8_t r);
    void LD_hl_n(std::uint8_t n);
    void LD_a_bc();
    void LD_a_de();
    void LD_a_nn(std::uint16_t nn);
    void LD_bc_a();
    void LD_de_a();
    void LD_nn_a(std::uint8_t n1, std::uint8_t n2);
    //void LD_a_i(); requires interrupt implementation, IFF2
    //void LD_a_r(); requires interrupt implementation, IFF2
    void LD_i_a();
    void LD_r_a();

    //---------------------------------------------------------------//
    // NO PREFIX - 16-bit Loads
    //---------------------------------------------------------------//

    void LD_dd_nn(std::uint8_t dd, std::uint8_t n1, std::uint8_t n2);
    void LD_hl_nn(std::uint8_t n1, std::uint8_t n2);
    void LD_nn_hl(std::uint16_t nn);
    // void LD_sp_hl(); i still gotta fix up the registers to be a union, probably
    void Push_qq(std::uint8_t qq);
    void Pop_qq(std::uint8_t qq);


    //---------------------------------------------------------------//
    // NO PREFIX - Exchange, Blkt, Search
    //---------------------------------------------------------------//

    void EX_de_hl();
    void EX_AF_AF2();
    void EXX();

    //---------------------------------------------------------------//
    // ED PREFIX - 16-bit Loads
    //---------------------------------------------------------------//

    void LD_dd_nn(std::uint8_t dd, std::uint16_t nn);
    void LD_nn_dd(std::uint8_t dd, std::uint16_t nn);

    //---------------------------------------------------------------//
    // DD PREFIX - 8-bit Loads
    //---------------------------------------------------------------//

    void LD_r_ixd(std::uint8_t r, std::uint8_t d);
    void LD_ixd_r(std::uint8_t d, std::uint8_t r);
    void LD_ixd_n(std::uint8_t d, std::uint8_t n);

    //---------------------------------------------------------------//
    // DD PREFIX - 16-bit Loads
    //---------------------------------------------------------------//

    void LD_ix_nn(std::uint8_t n1, std::uint8_t n2);
    void LD_ix_nn_indirect(std::uint16_t nn);
    void LD_nn_ix(std::uint16_t nn);
    // void LD_sp_ix(); i still gotta fix up the registers to be a union, probably
    void Push_ix();
    void Pop_ix();

    //---------------------------------------------------------------//
    // FD PREFIX - 8-bit Loads
    //---------------------------------------------------------------//

    void LD_r_iyd(std::uint8_t r, std::uint8_t d);
    void LD_iyd_r(std::uint8_t d, std::uint8_t r);
    void LD_iyd_n(std::uint8_t d, std::uint8_t n);

    //---------------------------------------------------------------//
    // FD PREFIX - 16-bit Loads
    //---------------------------------------------------------------//

    void LD_iy_nn(std::uint8_t n1, std::uint8_t n2);
    void LD_iy_nn_indirect(std::uint16_t nn);
    void LD_nn_iy(std::uint16_t nn);
    // void LD_sp_iy(); i still gotta fix up the registers to be a union, probably
    void Push_iy();
    void Pop_iy();
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
