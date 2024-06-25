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
// NO PREFIX - 8-bit loads
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

//---------------------------------------------------------------//
// NO PREFIX - 16-bit Loads
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

//---------------------------------------------------------------//
// NO PREFIX - Exchange, Blkt, Search
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

//---------------------------------------------------------------//
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

//---------------------------------------------------------------//
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

//---------------------------------------------------------------//
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


//---------------------------------------------------------------//
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

} // namespace trpp

