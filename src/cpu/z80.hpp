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
    explicit Z80();
    virtual ~Z80() = default;
    void ConnectMemory(ZxMemory* memory){ m_memory = memory;}

    // standard operational functions
    void Fetch();
    void Decode();
    void Execute();

    enum class InterruptMode{mode0, mode1, mode2};

  protected:
    // allow derived classes do whatever they want with these,
    // do not allow users access
    Z80RegisterSet m_regs;
    ZxMemory* m_memory; 
    // interrupts
    bool m_iff1;
    bool m_iff2;
    bool m_nmi;
    InterruptMode m_imode;

    // instruction operand tables:
    std::uint8_t& registerTable(std::uint8_t r);
    Z80RegisterPair& registerPairSPTable(std::uint8_t r); 
    Z80RegisterPair& registerPairAFTable(std::uint8_t r); 

  public:
    // memory addressing functions
    constexpr std::uint16_t formWord(std::uint8_t high, std::uint8_t low) const{
      return (static_cast<std::uint16_t>(high) << 8) | low;
    }

    // stack functions
    void PushByte(std::uint8_t byte);

  public:
    // flags status related
    struct Flags{
      static constexpr std::uint8_t Carry = 0x01;
      static constexpr std::uint8_t AddSubtract = 0x02;
      static constexpr std::uint8_t ParityOverflow = 0x04;
      static constexpr std::uint8_t HalfCarry = 0x0F;
      static constexpr std::uint8_t Zero = 0x40;
      static constexpr std::uint8_t Sign = 0x80;
    };

    enum class FlagRegister{
      f1, f2
    };

    std::uint8_t& GetFlagRegister(FlagRegister& f);
    void SetCarry(FlagRegister num);
    void SetAddSubtract(FlagRegister num);
    void SetParityOverflow(FlagRegister num);
    void SetHalfCarry(FlagRegister num);
    void SetZero(FlagRegister num);
    void SetSign(FlagRegister num);
    void ClearCarry(FlagRegister num);
    void ClearAddSubtract(FlagRegister num);
    void ClearParityOverflow(FlagRegister num);
    void ClearHalfCarry(FlagRegister num);
    void ClearZero(FlagRegister num);
    void ClearSign(FlagRegister num);

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
    void LD_a_i();
    void LD_a_r();
    void LD_i_a();
    void LD_r_a();

    //---------------------------------------------------------------//
    // NO PREFIX - 16-bit Loads
    //---------------------------------------------------------------//

    void LD_dd_nn(std::uint8_t dd, std::uint8_t n1, std::uint8_t n2);
    void LD_hl_nn(std::uint8_t n1, std::uint8_t n2);
    void LD_nn_hl(std::uint16_t nn);
    void LD_sp_hl();
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
    void LD_sp_ix();
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
    void LD_sp_iy();
    void Push_iy();
    void Pop_iy();
};

} // namespace trpp

#endif
