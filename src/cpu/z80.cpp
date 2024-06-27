#include "z80.hpp"
#include <stdexcept>

namespace trpp{

Z80::Z80():
  m_regs{},
  m_iff1{false},
  m_iff2{false},
  m_nmi{false},
  m_imode{InterruptMode::mode0}
{

}

void Z80::Decode(){

}

void Z80::PushByte(std::uint8_t byte){
  (*(m_memory))[--m_regs.sp] = byte;
}

std::uint8_t Z80::StackPopByte(){
  return (*(m_memory))[m_regs.sp++];
}

//---------------------------------------------------------------//
// OPCODE PARAMETERS TABLE DECODING
//---------------------------------------------------------------//

std::uint8_t& Z80::registerTable(std::uint8_t r){
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
      return (*(m_memory))[m_regs.hl1];
    case 0b111:
      return m_regs.a1;
    default:
      throw std::runtime_error{"unable to decode register r = 0b110"};
  }
}

Z80RegisterPair& Z80::registerPairSPTable(std::uint8_t r){
  switch(r){
    case 0b00:
      return m_regs.bc1;
    case 0b01:
      return m_regs.de1;
    case 0b10:
      return m_regs.hl1;
    case 0b11:
      return m_regs.sp;
    default:
      throw std::runtime_error{"unable to decode register pair"};
  }
}

Z80RegisterPair& Z80::registerPairAFTable(std::uint8_t r){
  switch(r){
    case 0b00:
      return m_regs.bc1;
    case 0b01:
      return m_regs.de1;
    case 0b10:
      return m_regs.hl1;
    case 0b11:
      return m_regs.af1;
    default:
      throw std::runtime_error{"unable to decode register pair"};
  }
}

//---------------------------------------------------------------//
// FLAGS / STATUS RELATED
//---------------------------------------------------------------//

std::uint8_t& Z80::GetFlagRegister(FlagRegister& f){
  switch(f){
    case FlagRegister::f1:
      return m_regs.f1;
    case FlagRegister::f2:
      return m_regs.f2;
  }
}

void Z80::SetCarry(FlagRegister num){
  std::uint8_t& f = GetFlagRegister(num);
  f &= Flags::Carry;
}

void Z80::SetAddSubtract(FlagRegister num){
  std::uint8_t& f = GetFlagRegister(num);
  f &= Flags::AddSubtract;
}

void Z80::SetParityOverflow(FlagRegister num){
  std::uint8_t& f = GetFlagRegister(num);
  f &= Flags::ParityOverflow;
}

void Z80::SetHalfCarry(FlagRegister num){
  std::uint8_t& f = GetFlagRegister(num);
  f &= Flags::HalfCarry;
}

void Z80::SetZero(FlagRegister num){
  std::uint8_t& f = GetFlagRegister(num);
  f &= Flags::Zero;
}

void Z80::SetSign(FlagRegister num){
  std::uint8_t& f = GetFlagRegister(num);
  f &= Flags::Sign;
}

void Z80::ClearCarry(FlagRegister num){
  std::uint8_t& f = GetFlagRegister(num);
  f &= ~Flags::Carry;
}

void Z80::ClearAddSubtract(FlagRegister num){
  std::uint8_t& f = GetFlagRegister(num);
  f &= ~Flags::AddSubtract;
}

void Z80::ClearParityOverflow(FlagRegister num){
  std::uint8_t& f = GetFlagRegister(num);
  f &= ~Flags::ParityOverflow;
}

void Z80::ClearHalfCarry(FlagRegister num){
  std::uint8_t& f = GetFlagRegister(num);
  f &= ~Flags::HalfCarry;
}

void Z80::ClearZero(FlagRegister num){
  std::uint8_t& f = GetFlagRegister(num);
  f &= ~Flags::Zero;
}

void Z80::ClearSign(FlagRegister num){
  std::uint8_t& f = GetFlagRegister(num);
  f &= ~Flags::Sign;
}

//---------------------------------------------------------------//
// OPCODE INSTRUCTIONS 
//---------------------------------------------------------------//
// 8-bit loads
//---------------------------------------------------------------//

void Z80::LD_r_r(std::uint8_t r, std::uint8_t rp){
  std::uint8_t& dest = registerTable(r);
  const std::uint8_t& src = registerTable(rp);
  dest = src;
}

void Z80::LD_r_n(std::uint8_t r, std::uint8_t n){
  std::uint8_t& dest = registerTable(r);
  dest = n;
}

void Z80::LD_r_hl(std::uint8_t r){
  std::uint8_t& dest = registerTable(r);
  dest = (*(m_memory))[m_regs.hl1];
}

void Z80::LD_hl_r(std::uint8_t r){
  const std::uint8_t& src = registerTable(r);
  (*(m_memory))[m_regs.hl1] = src;
}

void Z80::LD_hl_n(std::uint8_t n){
  (*(m_memory))[m_regs.hl1] = n;
}

void Z80::LD_a_bc(){ 
  m_regs.a1 = (*(m_memory))[m_regs.bc1];
}

void Z80::LD_a_de(){ 
  m_regs.a1 = (*(m_memory))[m_regs.de1];
}

void Z80::LD_a_nn(std::uint16_t nn){ 
  m_regs.a1 = (*(m_memory))[nn];
}

void Z80::LD_bc_a(){ 
  (*(m_memory))[m_regs.bc1] = m_regs.a1;
}

void Z80::LD_de_a(){ 
  (*(m_memory))[m_regs.de1] = m_regs.a1;
}

void Z80::LD_nn_a(std::uint8_t n1, std::uint8_t n2){
  std::uint16_t addr = formWord(n1, n2);
  (*(m_memory))[addr] = m_regs.a1;
}

void Z80::LD_a_i(){
  m_regs.a1 = m_regs.i;
  m_regs.i & 0x80 ? SetSign(FlagRegister::f1): ClearSign(FlagRegister::f1);
  m_regs.i == 0 ? SetZero(FlagRegister::f1): ClearZero(FlagRegister::f1);
  m_iff2 ? SetParityOverflow(FlagRegister::f1): ClearParityOverflow(FlagRegister::f1);
  ClearHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  throw 
    std::runtime_error{"If a interrupt occurs during execution of this, p/v=0"};
}

void Z80::LD_a_r(){
  m_regs.a1 = m_regs.r;
  m_regs.r & 0x80 ? SetSign(FlagRegister::f1): ClearSign(FlagRegister::f1);
  m_regs.r == 0 ? SetZero(FlagRegister::f1): ClearZero(FlagRegister::f1);
  m_iff2 ? SetParityOverflow(FlagRegister::f1): ClearParityOverflow(FlagRegister::f1);
  ClearHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  throw 
    std::runtime_error{"If a interrupt occurs during execution of this, p/v=0"};
}

void Z80::LD_i_a(){
  m_regs.i = m_regs.a1;
}

void Z80::LD_r_a(){
  m_regs.r = m_regs.a1;
}

// DD PREFIX - 8-bit Loads
//---------------------------------------------------------------//

void Z80::LD_r_ixd(std::uint8_t r, std::uint8_t d){
  std::uint8_t& dest = registerTable(r);
  dest = (*(m_memory))[m_regs.ix + d];
}

void Z80::LD_ixd_r(std::uint8_t d, std::uint8_t r){
  const std::uint8_t& src = registerTable(r);
  (*(m_memory))[m_regs.ix + d] = src;
}

void Z80::LD_ixd_n(std::uint8_t d, std::uint8_t n){
  (*(m_memory))[m_regs.ix + d] = n;
}

// FD PREFIX - 8-bit Loads
//---------------------------------------------------------------//

void Z80::LD_r_iyd(std::uint8_t r, std::uint8_t d){
  std::uint8_t& dest = registerTable(r);
  dest = (*(m_memory))[m_regs.iy + d];
}

void Z80::LD_iyd_r(std::uint8_t d, std::uint8_t r){
  const std::uint8_t& src = registerTable(r);
  (*(m_memory))[m_regs.iy + d] = src;
}

void Z80::LD_iyd_n(std::uint8_t d, std::uint8_t n){
  (*(m_memory))[m_regs.iy + d] = n;
}

//---------------------------------------------------------------//
// 16-bit Loads
//---------------------------------------------------------------//

void Z80::LD_dd_nn(std::uint8_t dd, std::uint8_t n1, std::uint8_t n2){
  // ddh <- nn+1, ddl <- nn
  std::uint16_t nn = formWord(n1, n2);
  Z80RegisterPair& rr = registerPairSPTable(dd);
  rr = nn;
}

void Z80::LD_hl_nn(std::uint8_t n1, std::uint8_t n2){
  m_regs.hl1 = (*(m_memory))[formWord(n1, n2)];
}

void Z80::LD_nn_hl(std::uint16_t nn){
  (*(m_memory))[nn] = m_regs.l1;
  (*(m_memory))[nn+1] = m_regs.h1;
}

void Z80::LD_sp_hl(){
  m_regs.sp = m_regs.hl1;
}

void Z80::Push_qq(std::uint8_t qq){
  Z80RegisterPair& rr = registerPairAFTable(qq);
  PushByte(rr.high);
  PushByte(rr.low);
}

void Z80::Pop_qq(std::uint8_t qq){
  Z80RegisterPair& rr = registerPairAFTable(qq);
  rr.low = (*(m_memory))[m_regs.sp++];
  rr.high = (*(m_memory))[m_regs.sp++];
}

// ED PREFIX - 16-bit Loads
//---------------------------------------------------------------//

void Z80::LD_dd_nn(std::uint8_t dd, std::uint16_t nn){
  Z80RegisterPair& rr = registerPairSPTable(dd);
  rr.low = (*(m_memory))[nn];
  rr.high = (*(m_memory))[nn+1];
}

void Z80::LD_nn_dd(std::uint8_t nn, std::uint16_t dd){
  Z80RegisterPair& rr = registerPairSPTable(dd);
  (*(m_memory))[nn] = rr.low;
  (*(m_memory))[nn+1] = rr.high;
}

// DD PREFIX - 16-bit Loads
//---------------------------------------------------------------//

void Z80::LD_ix_nn(std::uint8_t n1, std::uint8_t n2){
  std::uint16_t nn = formWord(n2, n1);
  m_regs.ix = nn;
}

void Z80::LD_ix_nn_indirect(std::uint16_t nn){
  m_regs.ix = 0;
  m_regs.ix.low = (*(m_memory))[nn];
  m_regs.ix.high =  (*(m_memory))[nn+1];
}

void Z80::LD_nn_ix(std::uint16_t nn){
  (*(m_memory))[nn] = m_regs.ix.low;
  (*(m_memory))[nn+1] = m_regs.ix.high;
}

void Z80::LD_sp_ix(){
  m_regs.sp = m_regs.ix;
}

void Z80::Push_ix(){
  const Z80RegisterPair& ix = m_regs.ix;
  PushByte(ix.high);
  PushByte(ix.low);
}

void Z80::Pop_ix(){
  std::uint8_t low = (*(m_memory))[m_regs.sp++];
  std::uint8_t high = (*(m_memory))[m_regs.sp++];
  m_regs.ix = 0;
  m_regs.ix.high = high;
  m_regs.ix.low = low;
}

// FD PREFIX - 16-bit Loads
//---------------------------------------------------------------//

void Z80::LD_iy_nn(std::uint8_t n1, std::uint8_t n2){
  std::uint16_t nn = formWord(n2, n1);
  m_regs.iy = nn;
}

void Z80::LD_iy_nn_indirect(std::uint16_t nn){
  m_regs.iy = 0;
  m_regs.iy.low = (*(m_memory))[nn];
  m_regs.iy.high =  (*(m_memory))[nn+1];
}

void Z80::LD_nn_iy(std::uint16_t nn){
  (*(m_memory))[nn] = m_regs.iy.low;
  (*(m_memory))[nn+1] = m_regs.iy.high;
}

void Z80::LD_sp_iy(){
  m_regs.sp = m_regs.iy;
}

void Z80::Push_iy(){
  const Z80RegisterPair& iy = m_regs.iy;
  PushByte(iy.high);
  PushByte(iy.low);
}

void Z80::Pop_iy(){
  std::uint8_t low = (*(m_memory))[m_regs.sp++];
  std::uint8_t high = (*(m_memory))[m_regs.sp++];
  m_regs.iy.high =  high;
  m_regs.iy.low = low;
}

//---------------------------------------------------------------//
// Exchange, Blkt, Search
//---------------------------------------------------------------//

void Z80::EX_de_hl(){
  std::uint16_t tmp = m_regs.de1;
  m_regs.de1 = m_regs.hl1;
  m_regs.hl1 = tmp;
}

void Z80::EX_AF_AF2(){
  // opcode = 00'0001'000 = 0x08
  std::uint16_t af = m_regs.af1;
  std::uint16_t af2 = m_regs.af2;
  // exchange the registers
  m_regs.af1 = af2;
  m_regs.af2 = af;
}

void Z80::EXX(){
  std::uint16_t tmpbc1 = m_regs.bc1;
  std::uint16_t tmpde1 = m_regs.de1;
  std::uint16_t tmphl1 = m_regs.hl1;
  // set the first set
  m_regs.bc1 = m_regs.bc2;
  m_regs.de1 = m_regs.de2;
  m_regs.hl1 = m_regs.hl2;
  // set the second set
  m_regs.bc2 = tmpbc1;
  m_regs.de2 = tmpde1;
  m_regs.hl2 = tmphl1;
}
    
void Z80::EX_sp_hl(){
  // H <-> (SP+1), L <->(SP)
  // temporary buffers
  std::uint8_t sp = (*(m_memory))[m_regs.sp];
  std::uint8_t spnext = (*(m_memory))[m_regs.sp+1];
  std::uint8_t h = m_regs.h1;
  std::uint8_t l = m_regs.l1;
  // now the swapping occurs
  m_regs.h1 = spnext;
  (*(m_memory))[m_regs.sp+1] = h;
  m_regs.l1 = sp;
  (*(m_memory))[m_regs.sp] = l;

}

// ED PREFIX - Exchange, Blkt, Search
//---------------------------------------------------------------//

void Z80::LDI(){
  //(DE) <- (HL), DE <- DE + 1, HL <- HL + 1, BC <- BC – 1

  std::uint16_t current_bc = m_regs.bc1;  // kept for testing pv flag
  // actual work
  (*(m_memory))[m_regs.de1] = (*(m_memory))[m_regs.hl1];
  m_regs.de1 = m_regs.de1 + 1;
  m_regs.hl1 = m_regs.hl1 + 1;
  m_regs.bc1 = m_regs.bc1 - 1;
  // now conditions!
  ClearHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  current_bc -1 != 0 ? SetParityOverflow(FlagRegister::f1) : 
    ClearParityOverflow(FlagRegister::f1);

}

void Z80::LDIR(){
  // repeat {(DE) <- (HL), DE <- DE + 1, HL <- HL + 1, BC <- BC – 1} while (BC ≠ 0)
  std::uint16_t current_bc = m_regs.bc1;  // kept for testing pv flag
  // actual work
  if(m_regs.bc1 != 0){
    (*(m_memory))[m_regs.de1] = (*(m_memory))[m_regs.hl1];
    m_regs.de1 = m_regs.de1 + 1;
    m_regs.hl1 = m_regs.hl1 + 1;
    m_regs.pc = m_regs.pc - 2;
    // conditions
    ClearHalfCarry(FlagRegister::f1);
    ClearAddSubtract(FlagRegister::f1);
    current_bc -1 != 0 ? SetParityOverflow(FlagRegister::f1) : 
      ClearParityOverflow(FlagRegister::f1);
  }
  else{ return; }
}

void Z80::LDD(){
  // (DE) <- (HL), DE <- DE – 1, HL <- HL– 1, BC <- BC– 1
  std::uint16_t current_bc = m_regs.bc1;  // kept for testing pv flag
  // actual work
  (*(m_memory))[m_regs.de1] = (*(m_memory))[m_regs.hl1];
  m_regs.de1 = m_regs.de1 - 1;
  m_regs.hl1 = m_regs.hl1 - 1;
  m_regs.bc1 = m_regs.bc1 - 1;
  // now conditions
  ClearHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  current_bc -1 != 0 ? SetParityOverflow(FlagRegister::f1) : 
    ClearParityOverflow(FlagRegister::f1);
}

void Z80::LDDR(){
  // (DE) <- (HL), DE <- DE – 1, HL <- HL– 1, BC <- BC– 1, PC-=2
  if(m_regs.bc1 != 0){
    LDD();
  }
  else{ return ;}
}

/*
void Z80::CPI(){
  // A – (HL), HL ← HL +1, BC ← BC – 1
  // testing for borrow:
}
*/

// DD PREFIX - Exchange, Blkt, Search
//---------------------------------------------------------------//

void Z80::EX_sp_ix(){
  // ix.high <-> (SP+1), ix.low <->(SP)
  // temporary buffers
  std::uint8_t sp = (*(m_memory))[m_regs.sp];
  std::uint8_t spnext = (*(m_memory))[m_regs.sp+1];
  std::uint8_t ix_high = m_regs.ix.high;
  std::uint8_t ix_low = m_regs.ix.low;
  // now the swapping occurs
  m_regs.ix.high = spnext;
  (*(m_memory))[m_regs.sp+1] = ix_high;
  m_regs.ix.low = sp;
  (*(m_memory))[m_regs.sp] = ix_low;

}

// FD PREFIX - Exchange, Blkt, Search
//---------------------------------------------------------------//

void Z80::EX_sp_iy(){
  // iy.high <-> (SP+1), iy.low <->(SP)
  // temporary buffers
  std::uint8_t sp = (*(m_memory))[m_regs.sp];
  std::uint8_t spnext = (*(m_memory))[m_regs.sp+1];
  std::uint8_t iy_high = m_regs.iy.high;
  std::uint8_t iy_low = m_regs.iy.low;
  // now the swapping occurs
  m_regs.iy.high = spnext;
  (*(m_memory))[m_regs.sp+1] = iy_high;
  m_regs.iy.low = sp;
  (*(m_memory))[m_regs.sp] = iy_low;
}

//---------------------------------------------------------------//
// General-Purpose Arithmetic and CPU Control Group
//---------------------------------------------------------------//

void Z80::CPL(){
  // A <-- A'
  m_regs.a1 = ~m_regs.a1;
  SetHalfCarry(FlagRegister::f1);
  SetAddSubtract(FlagRegister::f1);
}

void Z80::CCF(){
  // carry is inverted
  bool prevCarry = m_regs.f1 & Flags::Carry;
  prevCarry ? SetHalfCarry(FlagRegister::f1) : ClearHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  m_regs.f1 & Flags::Carry ? ClearCarry(FlagRegister::f1) : SetCarry(FlagRegister::f1);
}

void Z80::SCF(){
  // Carry is set
  ClearHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  SetCarry(FlagRegister::f1);
}

void Z80::NOP(){
  // does nothing!
}

void Z80::DI(){
  // IFF <-- 0
  m_iff1 = false;
  m_iff2 = false;
}

void Z80::EI(){
  // IFF <-- 1
  m_iff1 = true;
  m_iff2 = true;
}

// ED PREFIX - General-Purpose Arithmetic and CPU Control Group
//---------------------------------------------------------------//

/*
void Z80::NEG(){
  std::uint8_t before = m_regs.a1;
  std::uint8_t after = -m_regs.a1;
  m_regs.a1 = after;
  // statuses
  after & 0x80 ? SetSign(FlagRegister::f1) : ClearSign(FlagRegister::f1);
  after == 0 ? SetZero(FlagRegister::f1) : ClearZero(FlagRegister::f1);
  // BORROW!
  before == 0x80 ? SetParityOverflow(FlagRegister::f1) : ClearParityOverflow(FlagRegister::f1);
  SetAddSubtract(FlagRegister::f1);
  before != 0 ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);
}
*/

void Z80::IM0(){
  // sets to interrupt mode 0 
  m_imode = InterruptMode::mode0;
}

void Z80::IM1(){
  // sets to interrupt mode 1
  m_imode = InterruptMode::mode1;

}

void Z80::IM2(){
  // sets to interrupt mode 2
  m_imode = InterruptMode::mode2;
}

//---------------------------------------------------------------//
// Roate and Shift Group
//---------------------------------------------------------------//

void Z80::RLCA(){
 // The contents of the Accumulator (Register A) are rotated left 1 bit position. The sign bit
 // (bit 7) is copied to the Carry flag and also to bit 0.
  std::uint16_t current = m_regs.a1;
  current <<= 1;
  bool bit8 = current & 0x100;
  current |= bit8;
  m_regs.a1 = current & 0xFF;
  // conditions
  ClearHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  bit8 ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);

}

void Z80::RLA(){
  // The contents of the Accumulator (Register A) are rotated left 1 bit position through the
  // Carry flag. The previous contents of the Carry flag are copied to bit 0
  std::uint16_t current = m_regs.a1 | (m_regs.f1 & Flags::Carry << 8);
  current <<= 1;
  bool bit9 = current & 0x200;
  current |= bit9;
  m_regs.a1 = current & 0xFF;
  // conditions
  ClearHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  current & 0x200 ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);

}

void Z80::RRCA(){
  // The contents of the Accumulator (Register A) are rotated right 1 bit position. Bit 0 is 
  // copied to the Carry flag and also to bit 7.
  bool bit0 = m_regs.a1 & 1;
  m_regs.a1 >>= 1;
  m_regs.a1 |= (bit0 << 7);
  // conditions
  ClearHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  bit0 ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);
}


void Z80::RRA(){
  // The contents of the Accumulator (Register A) are rotated right 1 bit position through the
  // Carry flag. The previous contents of the Carry flag are copied to bit 7.
  bool abit0 = m_regs.a1 & 1;
  bool carry = m_regs.f1 & Flags::Carry;
  m_regs.a1 >>= 1;
  m_regs.a1 |= (carry << 7);
  // conditions
  ClearHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  abit0 ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);

}

void Z80::RLC_r(std::uint8_t r){
  // The contents of register r are rotated left 1 bit position. The sign bit
  // (bit 7) is copied to the Carry flag and also to bit 0.
  std::uint8_t& reg = registerTable(r);
  std::uint16_t current = reg;
  current <<= 1;
  bool bit8 = current & 0x100;
  current |= bit8;
  reg = current & 0xFF;
  // conditions
  current < 0 ? SetSign(FlagRegister::f1) : ClearSign(FlagRegister::f1);
  current == 0 ? SetZero(FlagRegister::f1) : ClearZero(FlagRegister::f1);
  ClearHalfCarry(FlagRegister::f1);
  IsEvenParity(current) ? SetParityOverflow(FlagRegister::f1) : ClearParityOverflow(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  bit8 ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);
}

void Z80::RLC_hl(){
  // The contents of address hl are rotated left 1 bit position. The sign bit
  // (bit 7) is copied to the Carry flag and also to bit 0.
  std::uint8_t& mem = (*(m_memory))[m_regs.hl1];
  std::uint16_t current = mem;
  current <<= 1;
  bool bit8 = current & 0x100;
  current |= bit8;
  mem = current & 0xFF;
  // conditions
  current < 0 ? SetSign(FlagRegister::f1) : ClearSign(FlagRegister::f1);
  current == 0 ? SetZero(FlagRegister::f1) : ClearZero(FlagRegister::f1);
  ClearHalfCarry(FlagRegister::f1);
  IsEvenParity(current) ? SetParityOverflow(FlagRegister::f1) : ClearParityOverflow(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  bit8 ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);
}

// so much of rlc instructions are repeated... probably should refactor

void Z80::RLC_ixd(std::uint8_t d){
  // The contents of memory address ix+d are rotated left 1 bit position. The sign bit
  // (bit 7) is copied to the Carry flag and also to bit 0.
  std::uint8_t& mem = (*(m_memory))[m_regs.ix + d];
  std::uint16_t current = mem;
  current <<= 1;
  bool bit8 = current & 0x100;
  current |= bit8;
  mem = current & 0xFF;
  // conditions
  current < 0 ? SetSign(FlagRegister::f1) : ClearSign(FlagRegister::f1);
  current == 0 ? SetZero(FlagRegister::f1) : ClearZero(FlagRegister::f1);
  ClearHalfCarry(FlagRegister::f1);
  IsEvenParity(current) ? SetParityOverflow(FlagRegister::f1) : ClearParityOverflow(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  bit8 ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);
}

void Z80::RLC_iyd(std::uint8_t d){
  // The contents of memory address iy+d are rotated left 1 bit position. The sign bit
  // (bit 7) is copied to the Carry flag and also to bit 0.
  std::uint8_t& mem = (*(m_memory))[m_regs.iy + d];
  std::uint16_t current = mem;
  current <<= 1;
  bool bit8 = current & 0x100;
  current |= bit8;
  mem = current & 0xFF;
  // conditions
  current < 0 ? SetSign(FlagRegister::f1) : ClearSign(FlagRegister::f1);
  current == 0 ? SetZero(FlagRegister::f1) : ClearZero(FlagRegister::f1);
  ClearHalfCarry(FlagRegister::f1);
  IsEvenParity(current) ? SetParityOverflow(FlagRegister::f1) : ClearParityOverflow(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  bit8 ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);
}

void Z80::DoRL(std::uint8_t& src){
  // c src = 9 bit value
  std::uint16_t current = src | ((m_regs.f1 & Flags::Carry) << 8);
  // shift once => c src 0 [10 bit value]
  current <<= 1;
  // check bit 8
  bool leadingBit = current & 0x100;
  current |= leadingBit;
  src = current & 0xFF;
  // conditions

  src & 0x80 ? SetSign(FlagRegister::f1) : ClearSign(FlagRegister::f1);
  src == 0 ? SetZero(FlagRegister::f1) : ClearZero(FlagRegister::f1);
  ClearHalfCarry(FlagRegister::f1);

  IsEvenParity(src) ? SetParityOverflow(FlagRegister::f1) : ClearParityOverflow(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  current & 0x200 ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);
}

void Z80::RL_r(std::uint8_t r){ 
  DoRL(registerTable(r)); 
}

void Z80::RL_hl(){
  DoRL((*(m_memory))[m_regs.hl1]);
}

void Z80::RL_ixd(std::uint8_t d){
  DoRL((*(m_memory))[m_regs.ix + d]);
}

void Z80::RL_iyd(std::uint8_t d){
  DoRL((*(m_memory))[m_regs.iy + d]);
}

void Z80::DoRRC(std::uint8_t& src){
  bool bit0 = src & 1;
  src >>= 1;
  src |= (bit0 << 7);
  // conditions
  ClearHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  bit0 ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);
}

void Z80::RRC_r(std::uint8_t r){ 
  DoRRC(registerTable(r)); 
}

void Z80::RRC_hl(){
  DoRRC((*(m_memory))[m_regs.hl1]);
}

void Z80::RRC_ixd(std::uint8_t d){
  DoRRC((*(m_memory))[m_regs.ix + d]);
}

void Z80::RRC_iyd(std::uint8_t d){
  DoRRC((*(m_memory))[m_regs.iy + d]);
}

void Z80::DoRR(std::uint8_t& src){
  // The contents of operand m are rotated right 1 bit position through the Carry flag. The 
  // contents of bit 0 are copied to the Carry flag and the previous contents of the Carry flag are
  // copied to bit 7.
  bool bit0 = src & 1;
  bool prevCarry = m_regs.f1 & Flags::Carry;
  src >>= 1;
  src |= (prevCarry << 7);
  // conditions
  src & 0x80 ? SetSign(FlagRegister::f1) : ClearSign(FlagRegister::f1);
  src == 0 ? SetZero(FlagRegister::f1) : ClearZero(FlagRegister::f1);
  ClearHalfCarry(FlagRegister::f1);
  IsEvenParity(src) ? SetParityOverflow(FlagRegister::f1) : ClearParityOverflow(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  bit0 ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);
}

void Z80::DoSLA(std::uint8_t& src){
  // arithemtic left shift into a + src
  bool leadingbit = src & (1 << 7);
  src *= 2;
  // conditions
  src & 0x80 ? SetSign(FlagRegister::f1) : ClearSign(FlagRegister::f1);
  src == 0 ? SetZero(FlagRegister::f1) : ClearZero(FlagRegister::f1);
  ClearHalfCarry(FlagRegister::f1);
  IsEvenParity(src) ? SetParityOverflow(FlagRegister::f1) : ClearParityOverflow(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  leadingbit ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);
}

void Z80::DoSRA(std::uint8_t& src){
  // arithmetic right shift
  bool leastbit = src & 1;
  bool leadingbit = src & (1 << 7);
  src >>= 1;
  src |= (leadingbit << 7);
  // conditions
  src & 0x80 ? SetSign(FlagRegister::f1) : ClearSign(FlagRegister::f1);
  src == 0 ? SetZero(FlagRegister::f1) : ClearZero(FlagRegister::f1);
  ClearHalfCarry(FlagRegister::f1);
  IsEvenParity(src) ? SetParityOverflow(FlagRegister::f1) : ClearParityOverflow(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  leastbit ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);
}

void Z80::DoSRL(std::uint8_t& src){
  // logical right shift
  bool leastbit = src & 1;
  src >>= 1;
  src &= 0x7F;
  // conditions
  ClearSign(FlagRegister::f1);
  src == 0 ? SetZero(FlagRegister::f1) : ClearZero(FlagRegister::f1);
  ClearHalfCarry(FlagRegister::f1);
  IsEvenParity(src) ? SetParityOverflow(FlagRegister::f1) : ClearParityOverflow(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  leastbit ? SetCarry(FlagRegister::f1) : ClearCarry(FlagRegister::f1);
}

/*
void Z80::RLD(){
  std::uint8_t old_hlLow = (*(m_memory))[m_regs.hl1] & 0xF;
  std::uint8_t old_hlHigh = ((*(m_memory))[m_regs.hl1] & 0xF0) >> 4;
  std::uint8_t old_a_low = m_regs.a1 & 0xF;
  // now we perform the swapping
  // (hl)
  std::uint8_t new_hl = (old_hlLow << 4) | old_a_low;
  (*(m_memory))[m_regs.hl1] = new_hl;
  // accumulator
  std::uint8_t new_a_low = old_hlHigh;
  m_regs.a1 &= 0xF0;
  m_regs.a1 |= new_a_low;
}
*/

/*
void Z80::RRD(){

}
*/

//---------------------------------------------------------------//
// Bit Set, Reset, Test Group
//---------------------------------------------------------------/

void Z80::BIT_b_r(std::uint8_t b, std::uint8_t r){
  if(!b_is_valid(b)){
    throw std::runtime_error{"invalid b operand in Z80::Bit_b_r"};
  }
  std::uint8_t val = registerTable(r);
  bool bit = val & (1 << b);
  // conditions
  bit ? ClearZero(FlagRegister::f1) : SetZero(FlagRegister::f1);
  SetHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  throw std::runtime_error{"S, P/V Unknown for Bit_b_r"};
}

void Z80::BIT_b_hl(std::uint8_t b){
  if(!b_is_valid(b)){
    throw std::runtime_error{"invalid b operand in Z80::Bit_b_r"};
  }
  std::uint8_t val = (*(m_memory))[m_regs.hl1];
  bool bit = val & (1 << b);
  // conditions
  bit ? ClearZero(FlagRegister::f1) : SetZero(FlagRegister::f1);
  SetHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  throw std::runtime_error{"S, P/V Unknown for Bit_b_r"};
}

void Z80::BIT_b_ixd(std::uint8_t b, std::uint8_t d){
  if(!b_is_valid(b)){
    throw std::runtime_error{"invalid b operand in Z80::Bit_b_r"};
  }
  std::uint8_t val = (*(m_memory))[m_regs.ix + d];
  bool bit = val & (1 << b);
  // conditions
  bit ? ClearZero(FlagRegister::f1) : SetZero(FlagRegister::f1);
  SetHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  throw std::runtime_error{"S, P/V Unknown for Bit_b_r"};
}

void Z80::BIT_b_iyd(std::uint8_t b, std::uint8_t d){
  if(!b_is_valid(b)){
    throw std::runtime_error{"invalid b operand in Z80::Bit_b_r"};
  }
  std::uint8_t val = (*(m_memory))[m_regs.iy + d];
  bool bit = val & (1 << b);
  // conditions
  bit ? ClearZero(FlagRegister::f1) : SetZero(FlagRegister::f1);
  SetHalfCarry(FlagRegister::f1);
  ClearAddSubtract(FlagRegister::f1);
  throw std::runtime_error{"S, P/V Unknown for Bit_b_r"};
}

void Z80::SET_b_r(std::uint8_t b, std::uint8_t r){
  std::uint8_t& reg = registerTable(r);
  reg |= (1 << b);
}

void Z80::SET_b_hl(std::uint8_t b){
  std::uint8_t& mem = (*(m_memory))[m_regs.hl1];
  mem |= (1 << b);
}

void Z80::SET_b_ixd(std::uint8_t b, std::int8_t d){
  std::uint8_t& mem = (*(m_memory))[m_regs.ix + d];
  mem |= (1 << b);
}

void Z80::SET_b_iyd(std::uint8_t b, std::int8_t d){
  std::uint8_t& mem = (*(m_memory))[m_regs.iy + d];
  mem |= (1 << b);
}

void Z80::RES_b_r(std::uint8_t b, std::uint8_t r){
  std::uint8_t& reg = registerTable(r);
  reg &= ~(1 << b);
}

void Z80::RES_b_hl(std::uint8_t b){
  std::uint8_t& mem = (*(m_memory))[m_regs.hl1];
  mem &= (1 << b);
}

void Z80::RES_b_ixd(std::uint8_t b, std::int8_t d){
  std::uint8_t& mem = (*(m_memory))[m_regs.ix + d];
  mem &= (1 << b);
}

void Z80::RES_b_iyd(std::uint8_t b, std::int8_t d){
  std::uint8_t& mem = (*(m_memory))[m_regs.iy + d];
  mem &= (1 << b);
}

//---------------------------------------------------------------//
// Jump Group
//---------------------------------------------------------------/

bool Z80::cc_status(std::uint8_t cc){
  switch(cc){
    case 0b000:
      return !GetZero();
    case 0b001:
      return GetZero();
    case 0b010:
      return !GetCarry();
    case 0b011:
      return GetCarry();
    case 0b100:
      return !GetParityOverflow();
    case 0b101:
      return GetParityOverflow();
    case 0b110:
      return !GetSign();
    case 0b111:
      return GetSign();
    default:
      throw std::runtime_error{"Z80::cc_status(cc) cc is unknown"};
  }
}

void Z80::JP_nn(std::uint16_t nn){
  // jumps to nn
  m_regs.pc = nn;
}

void Z80::JP_cc_nn(std::uint8_t cc, std::uint16_t nn){
  // jumps based on cc
  m_regs.pc = cc_status(cc) ? nn: m_regs.pc + 2;
}

void Z80::JR_e(std::int8_t e){
  // jump relative. displacement has to be calculated from e
  std::int16_t displacement = e + 2;
  m_regs.pc = m_regs.pc + displacement;
}

// the jumps depending on flag status are all very similiar => refactor?

void Z80::JR_c_e(std::int8_t e){
  // jump relative depending on C. displacement has to be calculated from e
  std::int16_t displacement = e + 2;
  if(GetCarry()){
    m_regs.pc = m_regs.pc + displacement;
  }
  else{
    m_regs.pc = m_regs.pc + 2;
  }
}

void Z80::JR_nc_e(std::int8_t e){
  // jump relative depending on ~C. displacement has to be calculated from e
  std::int16_t displacement = e + 2;
  if(!GetCarry()){
    m_regs.pc = m_regs.pc + displacement;
  }
  else{
    m_regs.pc = m_regs.pc + 2;
  }
}

void Z80::JR_z_e(std::int8_t e){
  // jump relative depending on Z. displacement has to be calculated from e
  std::int16_t displacement = e + 2;
  if(GetZero()){
    m_regs.pc = m_regs.pc + displacement;
  }
  else{
    m_regs.pc = m_regs.pc + 2;
  }
}

void Z80::JR_nz_e(std::int8_t e){
  // jump relative depending on Z. displacement has to be calculated from e
  std::int16_t displacement = e + 2;
  if(!GetZero()){
    m_regs.pc = m_regs.pc + displacement;
  }
  else{
    m_regs.pc = m_regs.pc + 2;
  }

}

void Z80::JP_hl(){
  // set the pc to hl
  m_regs.pc = m_regs.hl1;
}

void Z80::JP_ix(){
  // set the pc to ix
  m_regs.pc = m_regs.ix;
}

void Z80::JP_iy(){
  // set the pc to iy
  m_regs.pc = m_regs.iy;
}

void Z80::DJNZ_e(std::int8_t e){
  // relative jump if reg.B - 1 != 0, else normal
  std::int16_t displacement = e + 2;
  m_regs.b1 = m_regs.b1 - 1;
  if(m_regs.b1 != 0){
    m_regs.pc = m_regs.pc + displacement;
  }
  else{
    m_regs.pc = m_regs.pc + 2;
  }
}

//---------------------------------------------------------------//
// Call and Return Group
//---------------------------------------------------------------/

void Z80::CALL_nn(std::uint16_t nn){
  // SP-1 = pchigh, SP-2 = pclow, pc = nn
  std::uint8_t pclow = m_regs.pc & 0xFF;
  std::uint8_t pchigh = (m_regs.pc & (0xFF << 8)) >> 8;
  PushByte(pchigh);
  PushByte(pclow);
  m_regs.pc = nn;

}

void Z80::CALL_cc_nn(std::uint8_t cc, std::uint16_t nn){
  // conditional CALL on flag cc
  if(cc_status(cc)){
    std::uint8_t pclow = m_regs.pc & 0xFF;
    std::uint8_t pchigh = (m_regs.pc & (0xFF << 8)) >> 8;
    PushByte(pchigh);
    PushByte(pclow);
    m_regs.pc = nn;
  }

  else{
    m_regs.pc = m_regs.pc + 2;
  }
}

void Z80::RET(){
  // restore pc from the stack's CALL
  std::uint8_t pclow = StackPopByte();
  std::uint8_t pchigh = StackPopByte();
  // now form pc
  m_regs.pc = (static_cast<std::uint16_t>(pchigh) << 8) | pclow;
}

void Z80::RET_cc(std::uint8_t cc){
  // conditionally restore pc from the stack's CALL
  if(cc_status(cc)){
    std::uint8_t pclow = StackPopByte();
    std::uint8_t pchigh = StackPopByte();
    // now form pc
    m_regs.pc = (static_cast<std::uint16_t>(pchigh) << 8) | pclow;
  }
  else{
    m_regs.pc = m_regs.pc + 2;
  }
}

//void Z80::RETI();
//void Z80::RETN();

void Z80::RST(std::uint8_t t){
  // restart on the zero page somewhere, determined by t
  // is basically a CALL to zeropage somewhere 
  static std::uint8_t ptable[8] = {0x00, 0x08, 0x10, 0x18, 0x20, 0x28, 0x30, 0x38};
  if(t > 7){
    throw std::runtime_error{"RST param t is error"};
  }
  std::uint8_t pclow = m_regs.pc & 0xFF;
  std::uint8_t pchigh = (m_regs.pc & (0xFF << 8)) >> 8;
  PushByte(pchigh);
  PushByte(pclow);
  // now we set pc
  m_regs.pc = ptable[t];
}

} // namespace trpp

