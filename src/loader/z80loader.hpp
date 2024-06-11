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
#include "z80structs.hpp"

namespace trpp{

class Z80Loader : public BaseLoader{
  public:
  explicit Z80Loader(std::string&& filename);
  Z80Loader() = delete;
  Z80Loader(const Z80Loader& src) = delete;
  ~Z80Loader() = default;

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

  // convenient functions to help parse header information
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
