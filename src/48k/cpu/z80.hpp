#ifndef Z80_HPP
#define Z80_HPP

#include <cstdint>
#include <iostream>
#include "instruction.hpp"

namespace cpu{

struct Z80Registers{
  // standard register sets
  // first set
  std::uint8_t a1;
  std::uint8_t flags1;
  std::uint8_t bc1;
  std::uint8_t de1;
  std::uint8_t hl1;
  // second set
  std::uint8_t a2;
  std::uint8_t flags2;
  std::uint8_t bc2;
  std::uint8_t de2;
  std::uint8_t hl2;
  // special purpose registers
  std::uint16_t ir; // I+R register
  std::uint16_t ix;
  std::uint16_t iy;
  std::uint16_t sp;
  std::uint16_t pc;
};

class Z80{
  public:
  explicit Z80() = default;
  virtual ~Z80() = default;

  void Fetch();
  void Decode();
  void Execute();

  // instructions - it would be better if we had a instruction table

  protected:
  Instruction m_instruction;

  private:
  Z80Registers m_regs;
};

class DebugZ80: public Z80{
  public:
  explicit DebugZ80() = default;
  virtual ~DebugZ80() override = default;
  void SetInstruction(std::uint8_t* position);
  void SetInstruction(const Instruction& src);
  void PrintInstruction() const;
};

} // namespace cpu

#endif
