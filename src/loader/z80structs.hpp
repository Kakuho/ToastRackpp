#ifndef Z80STRUCTS_HPP
#define Z80STRUCTS_HPP

// convenient classes for .z80 file loading

#include <string>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <cassert>
#include <vector>

#include "baseLoader.hpp"

namespace trpp{

// these two enums are for system state
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

// used to capture the header of z80 files
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

// this is the state which the .z80 file encodes
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

} // namespace trpp

#endif
