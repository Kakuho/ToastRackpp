#ifndef Z80_HPP
#define Z80_HPP

// This is the universal Z80 class which will be used in the 48k and the
// 128k machines
//
// Reference: Zilog Z80 Manual

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <memory>
#include <format>
#include <cassert>

#include "../utils.hpp"
#include "io/ioport.hpp"
#include "z80registers.hpp"
#include "iospace.hpp"
#include "shared/zxmemory.hpp"

namespace Trpp::CPU{

class Z80Bridge;

class Z80{
  friend class Z80Bridge;
  public:
    enum class InterruptMode{mode0, mode1, mode2};
    //-------------------------------------------------------------
    // lifetime
    //-------------------------------------------------------------
  
    explicit Z80();
    virtual ~Z80() = default;
    void ConnectMemory(ZxMemory* memory){ m_memory = memory;}

    //-------------------------------------------------------------
    // Memory functions
    //-------------------------------------------------------------

    // memory addressing functions
    constexpr std::uint8_t GetByte(std::uint16_t address) const;
    constexpr void SetByte(std::uint16_t address, std::uint8_t value);
    constexpr std::uint16_t formWord(std::uint8_t high, std::uint8_t low) const;
    std::uint16_t ReadWord(std::uint16_t address) const;
    std::uint16_t ReadWord(std::uint16_t address);

    // stack functions
    void PushByte(std::uint8_t byte);
    std::uint8_t StackPopByte();

    //-------------------------------------------------------------
    // IO Space related
    //-------------------------------------------------------------

    void SetIoPort(std::uint8_t address, IO::IoPort& src){
      m_ports.SetPort(address, src);
    }

    void RemoveIoPort(std::uint8_t address, IO::IoPort& src){
      m_ports.RemovePort(address);
    }
    
  protected:
    //-------------------------------------------------------------
    // Internal Data Representation
    //-------------------------------------------------------------

    // allow derived classes do whatever they want with these,
    // but do not allow outside access
    
    // internal data
    Z80RegisterSet m_regs;
    IoSpace m_ports;
    std::uint8_t m_lastRead;
    // interrupts
    bool m_iff1;
    bool m_iff2;
    bool m_nmi;
    bool m_int;
    InterruptMode m_imode;
    bool m_halted;

    // external data
    ZxMemory* m_memory; 

    //-------------------------------------------------------------
    // Instruction operand tables
    //  decodes the input and provides the correct registers for use
    //-------------------------------------------------------------

    std::uint8_t& registerTable(std::uint8_t r);
    Z80RegisterPair& registerPairSPTable(std::uint8_t r); 
    Z80RegisterPair& registerPairAFTable(std::uint8_t r); 
    Z80RegisterPair& registerPairPPTable(std::uint8_t r); 
    Z80RegisterPair& registerPairRRTable(std::uint8_t r); 

    bool registerParamOkay(std::uint8_t r){ return r < 7;}

  public:
    //-------------------------------------------------------------
    // Flag related
    //-------------------------------------------------------------

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

    //---------------------------------------------------------------//
    // INSTRUCTIONS
    // (organised by instruction groups and page, prefix is at the end)
    //---------------------------------------------------------------//
    // 8-bit Loads Group
    //---------------------------------------------------------------//

    void LD_r_r(std::uint8_t r, std::uint8_t rp);   
    void LD_r_n(std::uint8_t r, std::uint8_t n);    
    void LD_r_hl(std::uint8_t r);                   
    void LD_r_ixd(std::uint8_t r, std::int8_t d);   // DD
    void LD_r_iyd(std::uint8_t r, std::int8_t d);  // FD
    void LD_hl_r(std::uint8_t r);                   
    void LD_ixd_r(std::int8_t d, std::uint8_t r);  // DD
    void LD_iyd_r(std::int8_t d, std::uint8_t r);  // FD
    void LD_hl_n(std::uint8_t n);                   
    void LD_ixd_n(std::int8_t d, std::uint8_t n);  // DD
    void LD_iyd_n(std::int8_t d, std::uint8_t n);  // FD
    void LD_a_bc();                                 
    void LD_a_de();                                 
    void LD_a_nn(std::uint16_t nn);                 
    void LD_bc_a();                                 
    void LD_de_a();                                 
    void LD_nn_a(std::uint16_t nn); 
    void LD_a_i();                                  // ED // Need Interrupt behaviour
    void LD_a_r();                                  // ED // Need Interrupt behaviour
    void LD_i_a();                                  // ED
    void LD_r_a();                                  // ED

    //---------------------------------------------------------------//
    // 16-bit Loads Group
    //---------------------------------------------------------------//

    void LD_dd_nn(std::uint8_t dd, 
        std::uint8_t n1, std::uint8_t n2);
    void LD_ix_nn(std::uint16_t nn);  // DD
    void LD_iy_nn(std::uint16_t nn);  // FD
    void LD_hl_nn(std::uint16_t nn);  
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
    void LDI();       // ED
    void LDIR();      // ED
    void LDD();       // ED
    void LDDR();      // ED
    void CPI();       // ED
    void CPIR();      // ED // requires Interrupt behaviour
    void CPD();       // ED
    void CPDR();      // ED // requires Interrupt behaviour
                      
    //---------------------------------------------------------------//
    // 8-bit Arithmetric Group
    //---------------------------------------------------------------//

    std::int8_t DoADD(const std::int8_t dest, const std::int8_t src);
    void ADD_a_r(std::uint8_t r);
    void ADD_a_n(std::int8_t n);
    void ADD_a_hl();
    void ADD_a_ixd(std::int8_t d);  // DD
    void ADD_a_iyd(std::int8_t d);  // FD

    // requires checking and testing! does CarryIn affects Overflow cond?
    std::int8_t DoADC(const std::int8_t dest, const std::int8_t src, bool carryIn);
    void ADC_a_r(std::uint8_t r);
    void ADC_a_n(std::int8_t n);
    void ADC_a_hl();
    void ADC_a_ixd(std::int8_t d);  // DD
    void ADC_a_iyd(std::int8_t d);  // FD

    std::int8_t DoSUB(const std::int8_t dest, const std::int8_t src);
    void SUB_a_r(std::uint8_t r);
    void SUB_a_n(std::int8_t n); // Two's comp?
    void SUB_a_hl();
    void SUB_a_ixd(std::int8_t d);  // DD
    void SUB_a_iyd(std::int8_t d);  // FD

    std::int8_t DoSBC(const std::int8_t dest, const std::int8_t src, bool carryIn);
    void SBC_a_r(std::uint8_t r);
    void SBC_a_n(std::int8_t n);
    void SBC_a_hl();
    void SBC_a_ixd(std::int8_t d);  // DD
    void SBC_a_iyd(std::int8_t d);  // FD


    std::int8_t DoAND(const std::uint8_t dest, const std::uint8_t src);
    void AND_a_r(std::uint8_t r);
    void AND_a_n(std::int8_t n);
    void AND_a_hl();
    void AND_a_ixd(std::int8_t d);  // DD
    void AND_a_iyd(std::int8_t d);  // FD

    std::int8_t DoOR(const std::uint8_t dest, const std::uint8_t src);
    void OR_a_r(std::uint8_t r);
    void OR_a_n(std::int8_t n);
    void OR_a_hl();
    void OR_a_ixd(std::int8_t d);  // DD
    void OR_a_iyd(std::int8_t d);  // FD

    std::int8_t DoXOR(const std::uint8_t dest, const std::uint8_t src);
    void XOR_a_r(std::uint8_t r);
    void XOR_a_n(std::int8_t n);
    void XOR_a_hl();
    void XOR_a_ixd(std::int8_t d);  // DD
    void XOR_a_iyd(std::int8_t d);  // FD

    void DoCP(const std::int8_t& src, const std::int8_t& dest);
    void CP_a_r(std::uint8_t r);
    void CP_a_n(std::int8_t n);
    void CP_a_hl();
    void CP_a_ixd(std::int8_t d);  // DD
    void CP_a_iyd(std::int8_t d);  // FD

    std::uint8_t DoINC(std::uint8_t src);
    void INC_r(std::uint8_t r);
    void INC_hl();
    void INC_ixd(std::int8_t d);    // DD
    void INC_iyd(std::int8_t d);    // FD

    std::uint8_t DoDEC(std::uint8_t src);
    void DEC_r(std::uint8_t r);
    void DEC_hl();
    void DEC_ixd(std::int8_t d);    // DD
    void DEC_iyd(std::int8_t d);    // FD

    //---------------------------------------------------------------//
    // General-Purpose Arithmetic and CPU Control Group
    //---------------------------------------------------------------//

    // void DAA() // BCD arithemtic adjustment for the accumulator
    void CPL();
    void NEG();   // ED 
    void CCF();
    void SCF();
    void NOP();
    void HALT(); // requires implementing the tick cycle
    void DI();
    void EI();
    void IM0();     // ED
    void IM1();     // ED
    void IM2();     // ED

    //---------------------------------------------------------------//
    // 16-bit Arithmetric Group
    //---------------------------------------------------------------//

    void ADD16_hl_ss(std::uint8_t ss);
    void ADC16_hl_ss(std::uint8_t ss);
    void SBC16_hl_ss(std::uint8_t ss);
    void ADD16_ix_pp(std::uint8_t ss);
    void ADD16_iy_rr(std::uint8_t ss);

    
    void INC16_ss(std::uint8_t ss);
    void INC16_ix();   // DD
    void INC16_iy(); 

    void DEC16_ss(std::uint8_t ss); 
    void DEC16_ix(); 
    void DEC16_iy(); 

    //---------------------------------------------------------------//
    // Rotate and Shift Group functions!!!
    //---------------------------------------------------------------/

    void RLCA();
    void RLA(); 
    void RRCA();
    void RRA();

    void RLC_r(std::uint8_t r);     // CB
    void RLC_hl();                  // CB
    void RLC_ixd(std::int8_t d);   // DDCB
    void RLC_iyd(std::int8_t d);   // FDCB
                                    //
    void DoRL(std::uint8_t& src);
    void RL_r(std::uint8_t r);      // CB
    void RL_hl();                   // CB
    void RL_ixd(std::int8_t d);    // DDCB
    void RL_iyd(std::int8_t d);    // FDCB

    void DoRRC(std::uint8_t& src);
    void RRC_r(std::uint8_t r);     // CB
    void RRC_hl();                  // CB
    void RRC_ixd(std::int8_t d);   // DDCB
    void RRC_iyd(std::int8_t d);   // FDCB
                                   
    void DoRR(std::uint8_t& src);
    void RR_r(std::uint8_t r);      // CB
    void RR_hl();                   // CB
    void RR_ixd(std::int8_t d);    // DDCB
    void RR_iyd(std::int8_t d);    // FDCB

    void DoSLA(std::uint8_t& src);
    void SLA_r(std::uint8_t r);      // CB
    void SLA_hl();                   // CB
    void SLA_ixd(std::int8_t d);    // DDCB
    void SLA_iyd(std::int8_t d);    // FDCB

    void DoSRA(std::uint8_t& src);
    void SRA_r(std::uint8_t r);      // CB
    void SRA_hl();                   // CB
    void SRA_ixd(std::int8_t d);    // DDCB
    void SRA_iyd(std::int8_t d);    // FDCB

    void DoSRL(std::uint8_t& src);
    void SRL_r(std::uint8_t r);      // CB
    void SRL_hl();                   // CB
    void SRL_ixd(std::int8_t d);    // DDCB
    void SRL_iyd(std::int8_t d);    // FDCB

    void RLD();                   // ED
    void RRD();                 // ED

    //---------------------------------------------------------------//
    // Bit Set, Reset, Test Group
    //---------------------------------------------------------------/

    // sanitary check
    bool b_is_valid(std::uint8_t b){ return b <= 7 ? true : false; }
    // a lot of these instructions have S and P/V unknown
    void BIT_b_r(std::uint8_t b, std::uint8_t r);           // CB
    void BIT_b_hl(std::uint8_t b);                          // CB
    void BIT_b_ixd(std::uint8_t b, std::int8_t d);         // DDCB
    void BIT_b_iyd(std::uint8_t b, std::int8_t d);         // FDCB
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
    void RETI(); 
    void RETN(); 
    void RST(std::uint8_t t);

    //---------------------------------------------------------------//
    // Input Output Group
    //---------------------------------------------------------------/
  
    void IN_a_n(std::uint8_t n);
    void IN_r_c(std::uint8_t r);
    void INI();
    void INIR();
    void IND();
    void INDR();
};

} // namespace Trpp::Cpu

#endif
