#include "z80loader.hpp"

namespace trpp{

  using header_type = Z80FileHeader;

  Z80Loader::Z80Loader(std::string&& filename): 
    BaseLoader(std::move(filename)),
    m_header{GetHeader()}
  {

  }

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

  std::uint8_t Z80Loader::ParseRefreshRegister() const{
    std::uint8_t major = ReadByte(11) & 0x7F;
    std::uint8_t minor = (ReadByte(12) & 0x1) << 7;
    return major | minor;
  }

} // namespace trpp
