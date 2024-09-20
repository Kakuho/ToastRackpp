#include "noprefix_table.hpp"

namespace trpp::instructions{

//-------------------------------------------------------------
// lifetime
//-------------------------------------------------------------

NoPrefixTable::NoPrefixTable(): m_buffer{}{
  m_buffer.fill(enums::Undefined);
  SetEntries();
}

void NoPrefixTable::SetEntries() noexcept{
  Set8BitLoadGroup();
  Set16BitLoadGroup();
  SetExchangeGroup();
  Set8bitAluGroup();
  SetGeneralGroup();
  Set16bitAluGroup();
  SetRotateShiftGroup();
  SetJumpGroup();
  SetCallReturnGroup();
}

void NoPrefixTable::Set8BitLoadGroup() noexcept{
  // ld r, r'
  m_buffer[0x7f] = enums::LD_r_r;
  m_buffer[0x78] = enums::LD_r_r;
  m_buffer[0x79] = enums::LD_r_r;
  m_buffer[0x7a] = enums::LD_r_r;
  m_buffer[0x7b] = enums::LD_r_r;
  m_buffer[0x7c] = enums::LD_r_r;
  m_buffer[0x7d] = enums::LD_r_r;
  m_buffer[0x47] = enums::LD_r_r;
  m_buffer[0x40] = enums::LD_r_r;
  m_buffer[0x41] = enums::LD_r_r;
  m_buffer[0x42] = enums::LD_r_r;
  m_buffer[0x43] = enums::LD_r_r;
  m_buffer[0x44] = enums::LD_r_r;
  m_buffer[0x45] = enums::LD_r_r;
  m_buffer[0x4f] = enums::LD_r_r;
  m_buffer[0x48] = enums::LD_r_r;
  m_buffer[0x49] = enums::LD_r_r;
  m_buffer[0x4a] = enums::LD_r_r;
  m_buffer[0x4b] = enums::LD_r_r;
  m_buffer[0x4c] = enums::LD_r_r;
  m_buffer[0x4d] = enums::LD_r_r;
  m_buffer[0x57] = enums::LD_r_r;
  m_buffer[0x50] = enums::LD_r_r;
  m_buffer[0x51] = enums::LD_r_r;
  m_buffer[0x52] = enums::LD_r_r;
  m_buffer[0x53] = enums::LD_r_r;
  m_buffer[0x54] = enums::LD_r_r;
  m_buffer[0x55] = enums::LD_r_r;
  m_buffer[0x5f] = enums::LD_r_r;
  m_buffer[0x58] = enums::LD_r_r;
  m_buffer[0x59] = enums::LD_r_r;
  m_buffer[0x5a] = enums::LD_r_r;
  m_buffer[0x5b] = enums::LD_r_r;
  m_buffer[0x5c] = enums::LD_r_r;
  m_buffer[0x5d] = enums::LD_r_r;
  m_buffer[0x67] = enums::LD_r_r;
  m_buffer[0x60] = enums::LD_r_r;
  m_buffer[0x61] = enums::LD_r_r;
  m_buffer[0x62] = enums::LD_r_r;
  m_buffer[0x63] = enums::LD_r_r;
  m_buffer[0x64] = enums::LD_r_r;
  m_buffer[0x65] = enums::LD_r_r;
  m_buffer[0x6f] = enums::LD_r_r;
  m_buffer[0x68] = enums::LD_r_r;
  m_buffer[0x69] = enums::LD_r_r;
  m_buffer[0x6a] = enums::LD_r_r;
  m_buffer[0x6b] = enums::LD_r_r;
  m_buffer[0x6c] = enums::LD_r_r;
  m_buffer[0x6d] = enums::LD_r_r;

  // ld r, n
  m_buffer[0x3e] = enums::LD_r_n;
  m_buffer[0x6 ] = enums::LD_r_n;
  m_buffer[0xe ] = enums::LD_r_n;
  m_buffer[0x16] = enums::LD_r_n;
  m_buffer[0x1e] = enums::LD_r_n;
  m_buffer[0x26] = enums::LD_r_n;
  m_buffer[0x2e] = enums::LD_r_n;

  // ld r, (hl)
  m_buffer[0x7e] = enums::LD_r_hl;
  m_buffer[0x46] = enums::LD_r_hl;
  m_buffer[0x4e] = enums::LD_r_hl;
  m_buffer[0x56] = enums::LD_r_hl;
  m_buffer[0x5e] = enums::LD_r_hl;
  m_buffer[0x66] = enums::LD_r_hl;
  m_buffer[0x6e] = enums::LD_r_hl;

  // ld (hl), r
  m_buffer[0x77] = enums::LD_hl_r;
  m_buffer[0x70] = enums::LD_hl_r;
  m_buffer[0x71] = enums::LD_hl_r;
  m_buffer[0x72] = enums::LD_hl_r;
  m_buffer[0x73] = enums::LD_hl_r;
  m_buffer[0x74] = enums::LD_hl_r;
  m_buffer[0x75] = enums::LD_hl_r;

  // ld (hl), n
  m_buffer[0x36] = enums::LD_hl_n;

  // ld a, (bc)
  m_buffer[0x0a] = enums::LD_a_bc;

  // ld a, (de)
  m_buffer[0x1a] = enums::LD_a_de;

  // ld a, (nn)
  m_buffer[0x3a] = enums::LD_a_nn;

  // ld (bc), a
  m_buffer[0x02] = enums::LD_bc_a;

  // ld de, a
  m_buffer[0x12] = enums::LD_de_a;

  // ld nn, a
  m_buffer[0x32] = enums::LD_nn_a;
}

void NoPrefixTable::Set16BitLoadGroup() noexcept{
  // ld dd, nn
  m_buffer[0x1 ] = enums::LD_dd_nn;
  m_buffer[0x11] = enums::LD_dd_nn;
  m_buffer[0x21] = enums::LD_dd_nn;
  m_buffer[0x31] = enums::LD_dd_nn;

  // ld hl, nn
  m_buffer[0x2a] = enums::LD_hl_nn;

  // ld nn, hl
  m_buffer[0x22] = enums::LD_nn_hl;

  // ld sp, hl
  m_buffer[0xf9] = enums::LD_sp_hl;

  // push qq
  m_buffer[0xc5] = enums::Push_qq;
  m_buffer[0xd5] = enums::Push_qq;
  m_buffer[0xe5] = enums::Push_qq;
  m_buffer[0xf5] = enums::Push_qq;
  
  // pop qq
  m_buffer[0xc1] = enums::Pop_qq;
  m_buffer[0xd1] = enums::Pop_qq;
  m_buffer[0xe1] = enums::Pop_qq;
  m_buffer[0xf1] = enums::Pop_qq;
}

void NoPrefixTable::SetExchangeGroup() noexcept{
  // ex de, hl
  m_buffer[0xeb] = enums::EX_de_hl;

  // ex af, af'
  m_buffer[0x08] = enums::EX_AF_AF2;

  // exx
  m_buffer[0xD9] = enums::EXX;

  // ex sp, hl
  m_buffer[0xe3] = enums::EX_sp_hl;
}

void NoPrefixTable::Set8bitAluGroup() noexcept{
  // add a, r
  m_buffer[0x87] = enums::ADD_a_r;
  m_buffer[0x80] = enums::ADD_a_r;
  m_buffer[0x81] = enums::ADD_a_r;
  m_buffer[0x82] = enums::ADD_a_r;
  m_buffer[0x83] = enums::ADD_a_r;
  m_buffer[0x84] = enums::ADD_a_r;
  m_buffer[0x85] = enums::ADD_a_r;

  // add a, n
  m_buffer[0xc6] = enums::ADD_a_n;

  // add a, hl
  m_buffer[0x86] = enums::ADD_a_hl;

  // adc a, r
  m_buffer[0x8f] = enums::ADC_a_r;
  m_buffer[0x88] = enums::ADC_a_r;
  m_buffer[0x89] = enums::ADC_a_r;
  m_buffer[0x8a] = enums::ADC_a_r;
  m_buffer[0x8b] = enums::ADC_a_r;
  m_buffer[0x8c] = enums::ADC_a_r;
  m_buffer[0x8d] = enums::ADC_a_r;

  // adc a, n
  m_buffer[0xce] = enums::ADC_a_n;

  // adc a, hl
  m_buffer[0x8e] = enums::ADC_a_hl;

  // sub a, r
  m_buffer[0x97] = enums::SUB_a_r;
  m_buffer[0x90] = enums::SUB_a_r;
  m_buffer[0x91] = enums::SUB_a_r;
  m_buffer[0x92] = enums::SUB_a_r;
  m_buffer[0x93] = enums::SUB_a_r;
  m_buffer[0x94] = enums::SUB_a_r;
  m_buffer[0x95] = enums::SUB_a_r;

  // sub a, n
  m_buffer[0xd6] = enums::SUB_a_n;

  // sub a, hl
  m_buffer[0x96] = enums::SUB_a_hl;
  
  // sbc a, r
  m_buffer[0x9f] = enums::SBC_a_r;
  m_buffer[0x98] = enums::SBC_a_r;
  m_buffer[0x99] = enums::SBC_a_r;
  m_buffer[0x9a] = enums::SBC_a_r;
  m_buffer[0x9b] = enums::SBC_a_r;
  m_buffer[0x9c] = enums::SBC_a_r;
  m_buffer[0x9d] = enums::SBC_a_r;
  
  // sbc a, n
  m_buffer[0xde] = enums::SBC_a_n;

  // sbc a, hl
  m_buffer[0x9e] = enums::SBC_a_hl;

  // and a, r 
  m_buffer[0xa7] = enums::AND_a_r;
  m_buffer[0xa0] = enums::AND_a_r;
  m_buffer[0xa1] = enums::AND_a_r;
  m_buffer[0xa2] = enums::AND_a_r;
  m_buffer[0xa3] = enums::AND_a_r;
  m_buffer[0xa4] = enums::AND_a_r;
  m_buffer[0xa5] = enums::AND_a_r;

  // and a, n
  m_buffer[0xe6] = enums::AND_a_n;

  // and a, hl
  m_buffer[0xa6] = enums::AND_a_hl;
  
  // or a, r
  m_buffer[0xb7] = enums::OR_a_r;
  m_buffer[0xb0] = enums::OR_a_r;
  m_buffer[0xb1] = enums::OR_a_r;
  m_buffer[0xb2] = enums::OR_a_r;
  m_buffer[0xb3] = enums::OR_a_r;
  m_buffer[0xb4] = enums::OR_a_r;
  m_buffer[0xb5] = enums::OR_a_r;

  // or a, n
  m_buffer[0xf6] = enums::OR_a_n;

  // or a, hl
  m_buffer[0xb6] = enums::OR_a_hl;

  // xor a, r
  m_buffer[0xaf] = enums::XOR_a_r;
  m_buffer[0xa8] = enums::XOR_a_r;
  m_buffer[0xa9] = enums::XOR_a_r;
  m_buffer[0xaa] = enums::XOR_a_r;
  m_buffer[0xab] = enums::XOR_a_r;
  m_buffer[0xac] = enums::XOR_a_r;
  m_buffer[0xad] = enums::XOR_a_r;

  // xor a, n
  m_buffer[0xee] = enums::XOR_a_n;

  // xor a, hl
  m_buffer[0xae] = enums::XOR_a_hl;

  // cp a, n
  m_buffer[0xbf] = enums::CP_a_n;
  m_buffer[0xb8] = enums::CP_a_n;
  m_buffer[0xb9] = enums::CP_a_n;
  m_buffer[0xba] = enums::CP_a_n;
  m_buffer[0xbb] = enums::CP_a_n;
  m_buffer[0xbc] = enums::CP_a_n;
  m_buffer[0xbd] = enums::CP_a_n;

  // cp a, n
  m_buffer[0xfe] = enums::CP_a_n;

  // cp, a, hl
  m_buffer[0xbe] = enums::CP_a_hl;

  // inc r
  m_buffer[0x3c] = enums::INC_r;
  m_buffer[0x04] = enums::INC_r;
  m_buffer[0x0c] = enums::INC_r;
  m_buffer[0x14] = enums::INC_r;
  m_buffer[0x1c] = enums::INC_r;
  m_buffer[0x24] = enums::INC_r;
  m_buffer[0x2c] = enums::INC_r;

  // inc hl
  m_buffer[0x34] = enums::INC_hl;

  // dec r
  m_buffer[0x3d] = enums::DEC_r;
  m_buffer[0x05] = enums::DEC_r;
  m_buffer[0x0d] = enums::DEC_r;
  m_buffer[0x15] = enums::DEC_r;
  m_buffer[0x1d] = enums::DEC_r;
  m_buffer[0x25] = enums::DEC_r;
  m_buffer[0x2d] = enums::DEC_r;

  // dec hl
  m_buffer[0x35] = enums::DEC_hl;
}

void NoPrefixTable::Set16bitAluGroup() noexcept{
  // add hl, ss
  m_buffer[0xc9] = enums::ADD_hl_ss;
  m_buffer[0xd9] = enums::ADD_hl_ss;
  m_buffer[0xe9] = enums::ADD_hl_ss;
  m_buffer[0xf9] = enums::ADD_hl_ss;

  // inc ss
  m_buffer[0x03] = enums::INC_ss;
  m_buffer[0x13] = enums::INC_ss;
  m_buffer[0x23] = enums::INC_ss;
  m_buffer[0x33] = enums::INC_ss;

  // dec ss
  m_buffer[0x0b] = enums::DEC_ss;
  m_buffer[0x1b] = enums::DEC_ss;
  m_buffer[0x2b] = enums::DEC_ss;
  m_buffer[0x3b] = enums::DEC_ss;
}

void NoPrefixTable::SetGeneralGroup() noexcept{
  // daa
  m_buffer[0x27] = enums::DAA;

  // cpl
  m_buffer[0x2f] = enums::CPL;

  // ccf
  m_buffer[0x3f] = enums::CCF;

  // scf
  m_buffer[0x37] = enums::SCF;

  // nop
  m_buffer[0x00] = enums::NOP;

  // halt
  m_buffer[0x76] = enums::HALT;

  // di
  m_buffer[0xf3] = enums::DI;

  // ei
  m_buffer[0xfb] = enums::EI;
}

void NoPrefixTable::SetRotateShiftGroup() noexcept{
  // rlca
  m_buffer[0x07] = enums::RLCA;

  // rla
  m_buffer[0x17] = enums::RLA;

  // rrca
  m_buffer[0x0f] = enums::RRCA;

  // rra
  m_buffer[0x1f] = enums::RRA;
}

void NoPrefixTable::SetJumpGroup() noexcept{
  // jp nn
  m_buffer[0xc3] = enums::JP_nn;

  // jp cc, nn
  m_buffer[0xfa] = enums::JP_cc_nn;
  m_buffer[0xc2] = enums::JP_cc_nn;
  m_buffer[0xca] = enums::JP_cc_nn;
  m_buffer[0xd2] = enums::JP_cc_nn;
  m_buffer[0xda] = enums::JP_cc_nn;
  m_buffer[0xe2] = enums::JP_cc_nn;
  m_buffer[0xea] = enums::JP_cc_nn;

  // jr e
  m_buffer[0x18] = enums::JR_e;

  // jr C, e
  m_buffer[0x38] = enums::JR_c_e;

  // jr nc, e
  m_buffer[0x30] = enums::JR_nc_e;

  // jr z, e 
  m_buffer[0x28] = enums::JR_z_e;

  // jr nz, e 
  m_buffer[0x20] = enums::JR_nz_e;

  // jp hl
  m_buffer[0xe9] = enums::JP_hl;

  // jp hl
  m_buffer[0x10] = enums::DJNZ_e;
}

void NoPrefixTable::SetCallReturnGroup() noexcept{
  // call nn
  m_buffer[0xcd] = enums::CALL_nn;

  // call cc, nn
  m_buffer[0xfc] = enums::CALL_cc_nn;
  m_buffer[0xc4] = enums::CALL_cc_nn;
  m_buffer[0xcc] = enums::CALL_cc_nn;
  m_buffer[0xd4] = enums::CALL_cc_nn;
  m_buffer[0xdc] = enums::CALL_cc_nn;
  m_buffer[0xe4] = enums::CALL_cc_nn;
  m_buffer[0xec] = enums::CALL_cc_nn;

  // ret
  m_buffer[0xc9] = enums::RET;

  // ret cc
  m_buffer[0xf8] = enums::RET_cc;
  m_buffer[0xc0] = enums::RET_cc;
  m_buffer[0xc8] = enums::RET_cc;
  m_buffer[0xd0] = enums::RET_cc;
  m_buffer[0xd8] = enums::RET_cc;
  m_buffer[0xe0] = enums::RET_cc;
  m_buffer[0xe8] = enums::RET_cc;

  // rst p
  m_buffer[0xff] = enums::RST;
  m_buffer[0xc7] = enums::RST;
  m_buffer[0xcf] = enums::RST;
  m_buffer[0xd7] = enums::RST;
  m_buffer[0xdf] = enums::RST;
  m_buffer[0xe7] = enums::RST;
  m_buffer[0xef] = enums::RST;
}

//-------------------------------------------------------------
// Operator Overloads
//-------------------------------------------------------------

[[nodiscard]] enums 
NoPrefixTable::operator[](std::size_t index) const{
  assert(index < TABLE_SIZE);
  return m_buffer[index];
}

}
