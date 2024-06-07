#include<cassert>
#include "cpu/z80.hpp"
#include "cpu/instruction.hpp"

void TryNOP(){
  cpu::DebugZ80 dz80{};
  cpu::InstructionROM rom{0x00};
  dz80.SetInstruction(&rom.buffer[0]);
  std::cout << std::hex;
  dz80.PrintInstruction();
}

int main(){

}
