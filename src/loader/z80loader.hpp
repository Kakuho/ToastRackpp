#ifndef Z80LOADER_HPP
#define Z80LOADER_HPP

// utilities for loading .z80 files

#include <string>
#include <cstdint>

#include "baseLoader.hpp"

namespace trpp{

class Z80Loader : public BaseLoader{
  public:

  Z80Loader(std::string&& filename): BaseLoader(std::move(filename)){

  }

  private:

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

  using header_type = Z80FileHeader;

  public:

  header_type ParseHeader() const{
    return header_type{};
  }

  private:
};

} // namespace trpp

#endif
