#ifndef Z80LOADER_HPP
#define Z80LOADER_HPP

// Class for loading .z80 files into system memory.
//
// Reference: https://worldofspectrum.org/faq/reference/z80format.htm

#include <stdexcept>
#include <string>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <cassert>
#include <vector>

#include "./../baseLoader.hpp"
#include "z80structs.hpp"
#include "z80enums.hpp"
#include "48k/zxmemory48k.hpp"

namespace Trpp::Loader{

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
  using header_type = Z80FileHeader;
  using info_type = Z80FileInfo;
  struct Unimplemented{};

  public:
    //-------------------------------------------------------------
    // Lifetime
    //-------------------------------------------------------------

    explicit Z80Loader(std::string&& filename);
    Z80Loader() = delete;
    Z80Loader(const Z80Loader& src) = delete;
    ~Z80Loader() = default;

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

    //-------------------------------------------------------------
    //  System Integration Functions
    //-------------------------------------------------------------

    void EasyDump48k() const{
      // procedure to dump the entire memory - this is only if uncompressed and easy!
      throw Unimplemented{};
    }

    //-------------------------------------------------------------
    //  Parsing Header Information
    //-------------------------------------------------------------

    std::uint8_t ParseRefreshRegister() const;
    header_type GetHeader() const;
    info_type GetFileInfo();

    //-------------------------------------------------------------
    //  Detection code
    //-------------------------------------------------------------

    bool IsVersion1(){ return m_header.pc != 0; }
    bool IsVersion2(){ return ReadWord(30) == 30; }
    bool IsVersion3(){ return (ReadWord(30) == 54) || (ReadWord(30) == 55); }

    Ver2SystemType DecodeVer2Model(){ return static_cast<Ver2SystemType>(ReadByte(34)); }
    Ver3SystemType DecodeVer3Model(){ return static_cast<Ver3SystemType>(ReadByte(34)); }

    std::string Z80VersionString(Z80FileVersion version) const;
    std::string SystemTypeString(Ver1SystemType) const { return "Zx Spectrum 48k";}
    std::string SystemTypeString(Ver2SystemType val) const;
    std::string SystemTypeString(Ver3SystemType val) const;

    //-------------------------------------------------------------
    // Printing Functions
    //-------------------------------------------------------------

    void PrintSpectrumModel() const;
    void PrintHeader() const;

  private:
    const header_type m_header;
    const info_type m_file_info;
    void virtual CheckFileName() const override{
  }
};

} // namespace trpp

#endif
