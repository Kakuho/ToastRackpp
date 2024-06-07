#ifndef INSTRUCTION_HPP
#define INSTRUCTION_HPP

#include <cstdint>
#include <iostream>
#include <initializer_list>
#include <ostream>
#include <string>
#include <vector>

namespace cpu{

enum class AddressingMode{one, two, three};

class Instruction{
  public:
  explicit Instruction() = default;
  explicit Instruction(std::uint8_t* pos);
  ~Instruction() = default;
  void operator=(std::uint8_t* position);

  void Read();

  std::uint16_t GetOpcode() const;

  private:
  std::uint8_t* m_pos;

  friend std::ostream& operator<<(std::ostream&, const Instruction&);
};

inline std::ostream& operator<<(std::ostream& ost, const Instruction& instr){
  return ost << static_cast<unsigned>(*instr.m_pos);
}

struct InstructionROM{
  InstructionROM(std::initializer_list<std::uint8_t> values);
  std::vector<std::uint8_t> buffer;
};

}

#endif
