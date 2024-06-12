#ifndef Z80LOADER_HPP
#define Z80LOADER_HPP

// utilities for loading .z80 files

#include <stdexcept>
#include <string>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <cassert>
#include <vector>

#include "baseLoader.hpp"
#include "z80structs.hpp"

namespace trpp{

// we could bit pack z80file type || ver2 sys / ver3 sys information
// together

enum class Z80FileVersion: std::uint8_t{
  ver1, ver2, ver3
};

enum class Ver1SystemType: std::uint8_t{
  foureightk
};

enum class Ver2SystemType: std::uint8_t{
  foureightk = 0,
  foureightInterface1 = 1,
  samram = 2,
  onetwoeightk = 3,
  onetwoeightkInterface1 = 4
};

enum class Ver3SystemType: std::uint8_t{
  foureightk = 0,
  foureightInterface1 = 1,
  samram = 2,
  foureightkMgt = 3,
  onetwoeightk = 4,
  onetwoeightkInterface1 = 5,
  onetwoeightkMgt = 6
};

struct Z80FileInfo{
  Z80FileVersion version; // 8 bits
  union HardwareModel{
    // 8 bits
    Ver1SystemType ver1Model;
    Ver2SystemType ver2Model;
    Ver3SystemType ver3Model;
  } model;
};

class Z80Loader : public BaseLoader{
  public:
  explicit Z80Loader(std::string&& filename);
  Z80Loader() = delete;
  Z80Loader(const Z80Loader& src) = delete;
  ~Z80Loader() = default;

  using header_type = Z80FileHeader;
  using info_type = Z80FileInfo;

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
  header_type GetHeader() const;
  info_type GetFileInfo();
  // detection code
  bool IsVersion1(){ return m_header.pc != 0; }
  bool IsVersion2(){ return ReadWord(30) == 30; }
  bool IsVersion3(){ return (ReadWord(30) == 54) || (ReadWord(30) == 55); }
  Ver2SystemType DecodeVer2Model(){ return static_cast<Ver2SystemType>(ReadByte(34)); }
  Ver3SystemType DecodeVer3Model(){ return static_cast<Ver3SystemType>(ReadByte(34)); }
  std::string Z80VersionString(Z80FileVersion version) const;
  std::string SystemTypeString(Ver1SystemType) const { return "Zx Spectrum 48k";}
  std::string SystemTypeString(Ver2SystemType val) const;
  std::string SystemTypeString(Ver3SystemType val) const;
  void PrintSpectrumModel() const;

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

  inline std::vector<std::uint8_t> EasyDump() const{
    // procedure to dump the entire memory - this is only if uncompressed and easy!
  }

  private:
  const header_type m_header;
  const info_type m_file_info;
  void virtual CheckFileName() const override{

  }
};

} // namespace trpp

#endif
