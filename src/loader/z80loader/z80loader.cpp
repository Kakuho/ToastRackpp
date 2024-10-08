#include "z80loader.hpp"
#include "loader/utils.hpp"
#include "loader/z80loader/decompression.hpp"
#include <stdexcept>

namespace Trpp::Loader{

using header_type = Z80FileHeader;
using info_type = Z80FileInfo;


//-------------------------------------------------------------=
//  Lifetime
//-------------------------------------------------------------

Z80Loader::Z80Loader(std::string& filename)
  :
    BaseLoader(filename),
    m_header{GetHeader()},
    m_file_info{GetFileInfo()}
{
  CheckFileName();
}

void Z80Loader::CheckFileName() const {
  Extension ext = ParseExtension(m_filename);
  assert(ext == Extension::Z80);
}

//-------------------------------------------------------------
//  System Integration Functions
//-------------------------------------------------------------

void Z80Loader::Load(ZxMemory48K& memory){
  if(IsVersion1()){
    std::cout << "Is Version1" << '\n';
    if(ReadByte(12) & 0b100000){
      DumpV1Uncompressed(memory);
    }
    else{
      DumpV1Compressed(memory);
    }
  }
  else if(IsVersion2()){
    std::cout << "Is Version2" << '\n';
    DumpV2Compressed(memory);
  }
  else if(IsVersion3()){
    std::cout << "Is Version3" << '\n';
    DumpV3Compressed(memory);
  }
  else{
      throw std::runtime_error{"Unrecognised .z80 version"};
  }
}

// V1 are only for 48k systems

void Z80Loader::DumpV1Uncompressed(ZxMemory48K& memory){
  // this procedure is to dump .z80 files when no compression is made.
  for(std::size_t i = 30; i < bytes.size(); i++){
    memory[i - 30] = bytes[i];
  }
}

void Z80Loader::DumpV1Compressed(ZxMemory48K& memory){
  auto decompressed = Z80::DecompressV1(
      reinterpret_cast<std::uint8_t*>(bytes.data())
  );
}

void Z80Loader::DumpV2Compressed(ZxMemory48K& memory){
  auto lut = Z80::DecompressV23(
      reinterpret_cast<std::uint8_t*>(bytes.data()+55),
      bytes.size() - 55
  );
}

void Z80Loader::DumpV3Compressed(ZxMemory48K& memory){
  auto lut = Z80::DecompressV23(
      reinterpret_cast<std::uint8_t*>(bytes.data()+86),
      bytes.size() - 86
  );
  std::size_t bytesindex = 0;
  for(const auto& [index, decompressedPage]: lut){
    std::cout << std::hex 
              << std::bitset<8>(index)
              << ' '
              << static_cast<unsigned>(index)
              << '\n';
    /*
    for(auto k: decompressedPage){
      std::cout << (static_cast<unsigned>(k)&0xFF) << ' ';
      bytesindex++;
      if(bytesindex % 16 == 0){
        std::cout << '\n';
      }
    }
    */
    if(Is48K()){
      std::uint16_t offset = 0;
      switch(index){
        case 4:
          offset = 0x8000;
          break;
        case 5:
          offset = 0xc000;
          break;
        case 8:
          offset = 0x4000;
          break;
        default:
          throw std::runtime_error{"IDK POTOTAOE SALADD"};
      }
      for(std::uint16_t i = 0; i < decompressedPage.size(); i++){
        memory[i + offset] = decompressedPage[i];
      }
    }
    else{
      throw std::runtime_error{"IDK what version is this"};
    }
  }
}

//-------------------------------------------------------------
//  Parsing Header Information
//-------------------------------------------------------------

header_type Z80Loader::GetHeader() const{
  std::uint8_t regA       = ReadByte(0);
  std::uint8_t regF       = ReadByte(1);
  std::uint16_t regBC     = ReadWord(2); 
  std::uint16_t regHL     = ReadWord(4); 
  std::uint16_t pc        = ReadWord(6); 
  std::uint16_t sp        = ReadWord(8); 
  std::uint8_t i          = ReadByte(10);
  std::uint8_t r          = ReadByte(11);
  std::uint8_t rsv_compressed_samrom_border_r7 = ReadByte(12);
  std::uint16_t regDE     = ReadWord(13);
  std::uint16_t regBC2    = ReadWord(15);
  std::uint16_t regDE2    = ReadWord(17);
  std::uint16_t regHL2    = ReadWord(19);
  std::uint8_t  regA2     = ReadByte(21);
  std::uint8_t  regF2     = ReadByte(22);
  std::uint16_t regIY     = ReadWord(23);
  std::uint16_t regIX     = ReadWord(25);
  std::uint8_t iflipflop  = ReadByte(27);
  std::uint8_t iff2       = ReadByte(28);
  std::uint8_t joystick_synch_ifreq_emulation_imode = ReadByte(29);

  // rvo?
  return header_type{
  regA,
  regF,
  regBC,
  regHL,
  pc,
  sp,
  i,
  r,
  rsv_compressed_samrom_border_r7,
  regDE,
  regBC2,
  regDE2,
  regHL2,
  regA2,
  regF2,
  regIY,
  regIX,
  iflipflop,
  iff2,
  joystick_synch_ifreq_emulation_imode
  };
}

info_type Z80Loader::GetFileInfo(){
  using enum Z80FileVersion;
  info_type fileinfo;
  if(IsVersion1()){
    using enum Ver1SystemType;
    fileinfo.version = ver1;
    fileinfo.model.ver1Model = foureightk;
  }
  else if(IsVersion2()){
    using enum Ver2SystemType;
    fileinfo.version = ver2;
    fileinfo.model.ver2Model = DecodeVer2Model();
  }
  else if(IsVersion3()){
    using enum Ver3SystemType;
    fileinfo.version = ver3;
    fileinfo.model.ver3Model = DecodeVer3Model();
  }
  return fileinfo;
}

std::uint8_t Z80Loader::ParseRefreshRegister() const{
  std::uint8_t major = ReadByte(11) & 0x7F;
  std::uint8_t minor = (ReadByte(12) & 0x1) << 7;
  return major | minor;
}

//-------------------------------------------------------------
// Detection Code
//-------------------------------------------------------------

std::string Z80Loader::Z80VersionString(Z80FileVersion version) const{
  switch(version){
    using enum Z80FileVersion;
    case ver1:
      return ".z80 Version 1";
    case ver2:
      return ".z80 Version 2";
    case ver3:
      return ".z80 Version 3";
  }
}

std::string Z80Loader::SystemTypeString(Ver2SystemType val) const{
  using enum Ver2SystemType;
  switch (val){
    case foureightk:
      return "Zx Spectrum 48k";
    case foureightInterface1:
      return "Zx Spectrum 48k Interface 1 Add on";
    case samram:
      return "Zx Spectrum with SamRam";
    case onetwoeightk:
      return "Zx Spectrum 128k";
    case onetwoeightkInterface1:
      return "Zx Spectrum 128k Interface 1 Add on";
  }
}

std::string Z80Loader::SystemTypeString(Ver3SystemType val) const{
  using enum Ver3SystemType;
  switch (val){
    case foureightk:
      return "Zx Spectrum 48k";
    case foureightInterface1:
      return "Zx Spectrum 48k Interface 1 Add on";
    case samram:
      return "Zx Spectrum with SamRam";
    case foureightkMgt:
      return "Zx Spectrum 48k MGT Add on";
    case onetwoeightk:
      return "Zx Spectrum 128k";
    case onetwoeightkInterface1:
      return "Zx Spectrum 128k Interface 1 Add on";
    case onetwoeightkMgt:
      return "Zx Spectrum 128k MGT Add on";
  }
}

//-------------------------------------------------------------
//  Printing Functions
//-------------------------------------------------------------

void Z80Loader::PrintSpectrumModel() const{
  std::string modelstring;
  switch(m_file_info.version){
    using enum Z80FileVersion;
    case ver1:
      modelstring = "Zx Spectrum 48k";
      break;
    case ver2:
      modelstring = SystemTypeString(m_file_info.model.ver2Model);
      break;
    case ver3:
      modelstring = SystemTypeString(m_file_info.model.ver3Model);
      break;
  }
  std::string versionstring = Z80VersionString(m_file_info.version);
  std::cout << "Z80 File version :: " << versionstring 
            << " :: machine :: " << modelstring << '\n';
}

void Z80Loader::PrintHeader() const{
  header_type header = GetHeader();
  std::cout << "register :: A :: " 
            << std::setw(2) << std::setfill('0') 
            << std::bitset<8>(header.regA).to_ulong() << '\n'

            << "register :: F :: " 
            << std::setw(2) << std::setfill('0') 
            << std::bitset<8>(header.regF).to_ulong() << '\n'

            << "register :: C :: " 
            << std::setw(2) << std::setfill('0') 
            << std::bitset<8>(header.regBC & 0xFF).to_ulong() << '\n'

            << "register :: B :: " 
            << std::setw(2) << std::setfill('0') 
            << std::bitset<8>(header.regBC >> 8).to_ulong() << '\n'

            << "register :: L :: " 
            << std::setw(2) << std::setfill('0') 
            << std::bitset<8>(header.regHL & 0xFF).to_ulong() << '\n'

            << "register :: H :: " 
            << std::setw(2) << std::setfill('0') 
            << std::bitset<8>(header.regHL >> 8).to_ulong() << '\n'

            << "register :: PC :: " 
            << std::setw(4) << std::setfill('0') 
            << std::bitset<16>(header.pc).to_ulong() << '\n'

            << "register :: SP :: " 
            << std::setw(4) << std::setfill('0') 
            << std::bitset<16>(header.sp).to_ulong() << '\n'

            << "register :: Interrupt :: " 
            << std::setw(4) << std::setfill('0') 
            << std::bitset<8>(header.i).to_ulong() << '\n'

            << "register :: Referesh :: " 
            << std::setw(2) << std::setfill('0') 
            << std::bitset<8>(header.r).to_ulong() << '\n'

            << "register :: reserved :: " 
            << std::setw(2) << std::setfill('0') 
            << std::bitset<8>(header.r).to_ulong() << '\n';
}

} // namespace Trpp::Loader
