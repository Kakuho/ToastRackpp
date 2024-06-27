#ifndef Z80_HPP
#define Z80_HPP

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <type_traits>

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
    std::uint8_t StackPopByte();


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

    // helper functions
    template<typename T>
      requires std::integral<T>
    constexpr bool IsEvenParity(T val){
      std::uint8_t count = 0;
      for(int i = 0; i < sizeof(T) * 8; i++){
        if((val & (1 << i)) == 1){
          count++;
        }
      }
      return count % 2 == 0 ? true : false;
    }

    std::uint8_t& GetFlagRegister(FlagRegister& f);
    // Sets
    void SetCarry(FlagRegister num);
    void SetAddSubtract(FlagRegister num);
    void SetParityOverflow(FlagRegister num);
    void SetHalfCarry(FlagRegister num);
    void SetZero(FlagRegister num);
    void SetSign(FlagRegister num);
    // Clears
    void ClearCarry(FlagRegister num);
    void ClearAddSubtract(FlagRegister num);
    void ClearParityOverflow(FlagRegister num);
    void ClearHalfCarry(FlagRegister num);
    void ClearZero(FlagRegister num);
    void ClearSign(FlagRegister num);
    // Gets
    bool GetCarry()           {return m_regs.f1 & Flags::Carry;}
    bool GetAddSubtract()     {return m_regs.f1 & Flags::AddSubtract;}
    bool GetParityOverflow()  {return m_regs.f1 & Flags::ParityOverflow;}
    bool GetHalfCarry()       {return m_regs.f1 & Flags::HalfCarry;}
    bool GetZero()            {return m_regs.f1 & Flags::Zero;}
    bool GetSign()            {return m_regs.f1 & Flags::Sign;}

  public:
    //---------------------------------------------------------------//
    // INSTRUCTIONS
    // (organised by instruction groups and page, prefix is at the end)
    //---------------------------------------------------------------//
    // 8-bit Loads Group
    //---------------------------------------------------------------//

    void LD_r_r(std::uint8_t r, std::uint8_t rp);   
    void LD_r_n(std::uint8_t r, std::uint8_t n);    
    void LD_r_hl(std::uint8_t r);                   
    void LD_r_ixd(std::uint8_t r, std::uint8_t d);  // DD
    void LD_r_iyd(std::uint8_t r, std::uint8_t d);  // FD
    void LD_hl_r(std::uint8_t r);                   
    void LD_ixd_r(std::uint8_t d, std::uint8_t r);  // DD
    void LD_iyd_r(std::uint8_t d, std::uint8_t r);  // FD
    void LD_hl_n(std::uint8_t n);                   
    void LD_ixd_n(std::uint8_t d, std::uint8_t n);  // DD
    void LD_iyd_n(std::uint8_t d, std::uint8_t n);  // FD
    void LD_a_bc();                                 
    void LD_a_de();                                 
    void LD_a_nn(std::uint16_t nn);                 
    void LD_bc_a();                                 
    void LD_de_a();                                 
    void LD_nn_a(std::uint8_t n1, std::uint8_t n2); 
    void LD_a_i();                                  // ED
    void LD_a_r();                                  // ED
    void LD_i_a();                                  // ED
    void LD_r_a();                                  // ED

    //---------------------------------------------------------------//
    // 16-bit Loads Group
    //---------------------------------------------------------------//

    void LD_dd_nn(std::uint8_t dd, 
        std::uint8_t n1, std::uint8_t n2);
    void LD_ix_nn(std::uint8_t n1, std::uint8_t n2);  // DD
    void LD_iy_nn(std::uint8_t n1, std::uint8_t n2);  // FD
    void LD_hl_nn(std::uint8_t n1, std::uint8_t n2);  
    void LD_dd_nn(std::uint8_t dd, std::uint16_t nn); // ED
    void LD_ix_nn_indirect(std::uint16_t nn);         // DD
    void LD_iy_nn_indirect(std::uint16_t nn);         // FD
    void LD_nn_hl(std::uint16_t nn);                  
    void LD_nn_dd(std::uint8_t dd, std::uint16_t nn); // ED
    void LD_nn_ix(std::uint16_t nn);                  // DD
    void LD_nn_iy(std::uint16_t nn);                  // FD
    void LD_sp_hl();
    void LD_sp_ix();                                  // DD
    void LD_sp_iy();                                  // FD
    void Push_qq(std::uint8_t qq);                    
    void Push_ix();                                   // DD
    void Push_iy();                                   // FD
    void Pop_qq(std::uint8_t qq);
    void Pop_ix();                                    // DD
    void Pop_iy();                                    // FD

    //---------------------------------------------------------------//
    // Exchange, Blkt, Search Group
    //---------------------------------------------------------------//

    void EX_de_hl();
    void EX_AF_AF2();
    void EXX();
    void EX_sp_hl();
    void EX_sp_ix();  // DD
    void EX_sp_iy();  // FD
    void LDI();
    void LDIR();
    void LDD();
    void LDDR();
    //void CPI();  // i need to figure out how to implement half borrowing here 
    //void CPIR(); // i need to figure out how to implement half borrowing here 
    //void CPD();  // i need to figure out how to implement half borrowing here   
    //void CPDR(); // figure out how to implement half borrow 

    //---------------------------------------------------------------//
    // General-Purpose Arithmetic and CPU Control Group
    //---------------------------------------------------------------//

    // void DAA() // BCD arithemtic adjustment for the accumulator
    void CPL();
    //void NEG();   // ED  // borrow from bit 4
    void CCF();
    void SCF();
    void NOP();
    //void HALT(); // requires implementing the tick cycle
    void DI();
    void EI();
    void IM0();     // ED
    void IM1();     // ED
    void IM2();     // ED

    //---------------------------------------------------------------//
    // Rotate and Shift Group functions
    //---------------------------------------------------------------/

    void RLCA();
    void RLA(); 
    void RRCA();
    void RRA();
    void RLC_r(std::uint8_t r);     // CB
    void RLC_hl();                  // CB
    void RLC_ixd(std::uint8_t d);   // DDCB
    void RLC_iyd(std::uint8_t d);   // FDCB
    void RL_r(std::uint8_t r);      // CB
    void RL_hl();                   // CB
    void RL_ixd(std::uint8_t d);    // DDCB
    void RL_iyd(std::uint8_t d);    // FDCB
    void RRC_r(std::uint8_t r);     // CB
    void RRC_hl();                  // CB
    void RRC_ixd(std::uint8_t d);   // DDCB
    void RRC_iyd(std::uint8_t d);   // FDCB
    //
    //void RLD();                   // ED // conditions need some working out
    //void RRD();                   // ED // conditions need some working out

    // helper functions for RL instructions
    void DoRL(std::uint8_t& src);
    void DoRRC(std::uint8_t& src);
    void DoRR(std::uint8_t& src);
    void DoSLA(std::uint8_t& src);
    void DoSRA(std::uint8_t& src);
    void DoSRL(std::uint8_t& src);

    //---------------------------------------------------------------//
    // Bit Set, Reset, Test Group
    //---------------------------------------------------------------/

    // sanitary check
    bool b_is_valid(std::uint8_t b){ return b <= 7 ? true : false; }
    // a lot of these instructions have S and P/V unknown
    void BIT_b_r(std::uint8_t b, std::uint8_t r);           // CB
    void BIT_b_hl(std::uint8_t b);                          // CB
    void BIT_b_ixd(std::uint8_t b, std::uint8_t d);         // DDCB
    void BIT_b_iyd(std::uint8_t b, std::uint8_t d);         // FDCB
    void SET_b_r(std::uint8_t b, std::uint8_t r);           // CB
    void SET_b_hl(std::uint8_t b);                          // CB
    void SET_b_ixd(std::uint8_t b, std::int8_t d);          // DDCB
    void SET_b_iyd(std::uint8_t b, std::int8_t d);          // FDCB
    void RES_b_r(std::uint8_t b, std::uint8_t r);           // CB
    void RES_b_hl(std::uint8_t b);                          // CB
    void RES_b_ixd(std::uint8_t b, std::int8_t d);          // DDCB
    void RES_b_iyd(std::uint8_t b, std::int8_t d);          // FDCB
                                                            
    //---------------------------------------------------------------//
    // Jump Group
    //---------------------------------------------------------------/

    bool cc_status(std::uint8_t cc);
    void JP_nn(std::uint16_t nn);
    void JP_cc_nn(std::uint8_t cc, std::uint16_t nn);
    void JR_e(std::int8_t e);
    void JR_c_e(std::int8_t e);
    void JR_nc_e(std::int8_t e);
    void JR_z_e(std::int8_t e);
    void JR_nz_e(std::int8_t e);
    void JP_hl();
    void JP_ix();                 // DD
    void JP_iy();                 // FD
    void DJNZ_e(std::int8_t e);

    //---------------------------------------------------------------//
    // Call and Return Group
    //---------------------------------------------------------------/

    void CALL_nn(std::uint16_t nn);
    void CALL_cc_nn(std::uint8_t cc, std::uint16_t nn);
    void RET();
    void RET_cc(std::uint8_t cc);
    //void RETI(); // gotta know how interrupts behave to implement this
    //void RETN(); // gotta know how interrupts behave to implement this
    void RST(std::uint8_t t);

    //---------------------------------------------------------------//
    // Input Output Group
    //---------------------------------------------------------------/
    // requires implementing ports 
    // how do we initialise ports ? idk
};

} // namespace trpp

#endif
