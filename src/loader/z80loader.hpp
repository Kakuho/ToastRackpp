#ifndef Z80LOADER_HPP
#define Z80LOADER_HPP

// utilities for loading .z80 files

#include <string>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <cassert>
#include <vector>

#include "baseLoader.hpp"

namespace trpp{

class Z80Loader : public BaseLoader{
  public:
  explicit Z80Loader(std::string&& filename);
  Z80Loader() = delete;
  Z80Loader(const Z80Loader& src) = delete;
  ~Z80Loader() = default;

  struct Z80FileHeader{
    std::uint8_t regA;
    std::uint8_t regF;
    std::uint16_t regBC;
    std::uint16_t regHL;
    std::uint16_t pc;
    std::uint16_t sp;
    std::uint8_t i;
    std::uint8_t r;
    std::uint8_t rsv_compressed_samrom_border_r7;
    std::uint16_t regDE;
    std::uint16_t regBC2;
    std::uint16_t regDE2;
    std::uint16_t regHL2;
    std::uint8_t regA2;
    std::uint8_t regF2;
    std::uint16_t regIY;
    std::uint16_t regIX;
    std::uint8_t iflipflop;
    std::uint8_t iff22;
    std::uint8_t joystick_synch_ifreq_emulation_imode;
  };

  enum class BorderColor : std::uint8_t{
    black = 0,
    blue = 1,
    red = 2,
    magenta = 3,
    green = 4, 
    cyan = 5,
    yellow = 6,
    white = 7
  };

  enum class InterruptMode{
    Mode1,
    Mode2,
    Mode3
  };

  struct Z80StateSnapshot{
    // first set of regs
    std::uint8_t regA;
    std::uint8_t regF;
    std::uint8_t regB;
    std::uint8_t regC;
    std::uint8_t regH;
    std::uint8_t regL;
    std::uint8_t regD;
    std::uint8_t regE;
    // second set of regs
    std::uint8_t regA2;
    std::uint8_t regF2;
    std::uint8_t regB2;
    std::uint8_t regC2;
    std::uint8_t regH2;
    std::uint8_t regL2;
    std::uint8_t regD2;
    std::uint8_t regE2;
    std::uint8_t interrupt;
    std::uint8_t refresh;
    std::uint16_t pc;
    std::uint16_t sp;
    std::uint16_t regIY;
    std::uint16_t regIX;
    BorderColor border;
    InterruptMode imode;
    bool HasSamRom;
    bool IsCompressed;
    bool interruptMasked;
  };

  using header_type = Z80FileHeader;

  void testReadWord(){
    std::uint16_t value = ReadWord(8); 
    std::cout << std::bitset<16>(value).to_ulong() << '\n';
    std::uint8_t byte1 = ReadByte(8);
    std::uint8_t byte2 = ReadByte(9);
    std::uint16_t word = (static_cast<std::uint16_t>(byte2) << 8) | byte1;
    std::uint16_t word2 = ReadWord(8);
    assert(word == 0x6a9a);
    assert(word2 == word);
    std::cout << std::bitset<8>(byte1).to_ulong() << '\n';
    std::cout << std::bitset<8>(byte2).to_ulong() << '\n';
    std::cout << std::bitset<16>(word).to_ulong() << '\n';
  }

  // convenient functions to help out with the header functions
  std::uint8_t ParseRefreshRegister() const;
  void ParseHeader();
  header_type GetHeader() const;

  // printer
  void PrintHeader() const{
    header_type header = GetHeader();
    std::cout << "register :: A :: " 
              << std::setw(2) << std::setfill('0') << std::bitset<8>(header.regA).to_ulong() << '\n'
              << "register :: F :: " 
              << std::setw(2) << std::setfill('0') << std::bitset<8>(header.regF).to_ulong() << '\n'
              << "register :: C :: " 
              << std::setw(2) << std::setfill('0') << std::bitset<8>(header.regBC & 0xFF).to_ulong() << '\n'
              << "register :: B :: " 
              << std::setw(2) << std::setfill('0') << std::bitset<8>(header.regBC >> 8).to_ulong() << '\n'
              << "register :: L :: " 
              << std::setw(2) << std::setfill('0') << std::bitset<8>(header.regHL & 0xFF).to_ulong() << '\n'
              << "register :: H :: " 
              << std::setw(2) << std::setfill('0') << std::bitset<8>(header.regHL >> 8).to_ulong() << '\n'
              << "register :: PC :: " 
              << std::setw(4) << std::setfill('0') << std::bitset<16>(header.pc).to_ulong() << '\n'
              << "register :: SP :: " 
              << std::setw(4) << std::setfill('0') << std::bitset<16>(header.sp).to_ulong() << '\n'
              << "register :: Interrupt :: " 
              << std::setw(4) << std::setfill('0') << std::bitset<8>(header.i).to_ulong() << '\n'
              << "register :: Referesh :: " 
              << std::setw(2) << std::setfill('0') << std::bitset<8>(header.r).to_ulong() << '\n'
              << "register :: reserved :: " 
              << std::setw(2) << std::setfill('0') << std::bitset<8>(header.r).to_ulong() << '\n';
  }

  inline std::vector<std::uint8_t> Dump() const{
    // procedure to dump the entire memory - this is only if uncompressed and easy!
  }

  private:
  const header_type m_header;
  void virtual CheckFileName() const override{

  }
};

} // namespace trpp

#endif
