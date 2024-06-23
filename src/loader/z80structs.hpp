#ifndef Z80STRUCTS_HPP
#define Z80STRUCTS_HPP

// convenient sructs for .z80 file loading

#include <string>
#include <cstdint>
#include <iostream>
#include <bitset>
#include <cassert>
#include <vector>

#include "baseLoader.hpp"

namespace trpp{

// these two enums are for system state - probably should be moved within system
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

// structs used to capture / store header of z80 files

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

struct Z80FileHeaderVersion2{
  std::uint16_t length;
  std::uint16_t pc;
  std::uint8_t hwmode;
  std::uint8_t samram;
  std::uint8_t byte36;
  std::uint8_t remu_ldiremu_aysound_audioboxemu_hwmodified;
  std::uint8_t lastsoundchipout;
  std::uint8_t soundchipdata[16];
};

struct Z80FileHeaderVersion3{
  std::uint16_t lowTStateCounter;
  std::uint8_t hiTStateCounter;
  std::uint8_t SpectatorFlagByte;
  std::uint8_t MGTRomPaged;
  std::uint8_t MultifaceRomPaged;
  std::uint8_t firstHalfRom;
  std::uint8_t lastHalfRom;
  std::uint16_t kbmapping[5];
  std::uint16_t mappingAscii[5];
  std::uint8_t MGTType;
  std::uint8_t DiscipleInhibitButtonStatus;
  std::uint8_t DiscipleInhibitFlag;
  std::uint8_t last1ffd_out;
};

// this is the state which the .z80 file encodes - the "payload"
// fields are laid out as in the file
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
