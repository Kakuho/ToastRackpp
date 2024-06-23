#ifndef CPULOGGER_HPP
#define CPULOGGER_HPP

#include <iostream>
#include <iomanip>
#include "z80registers.hpp"

namespace trpp{

class DebugZ80;

}

namespace trpp{

class CpuLogger{
  public:

    enum class NoPrefix{
      EX_AF_AF2 = 0x08,
      LD_dd_nn
    };

    enum class Verbosity{
      verbose,
      instructionLevel
    };

    void StartInstruction(Z80Registers& registers, NoPrefix code){
      std::cout << "Before: " << '\n' << "----------\n";
      Log(registers, code);
    }

    void EndInstruction(Z80Registers& registers, NoPrefix code){
      std::cout << "After: " << '\n' << "----------\n";
      Log(registers, code);
    }

    void Log(Z80Registers& registers, NoPrefix code){
      switch(code){
        using enum NoPrefix;
        case EX_AF_AF2:
          Log_EX_AF_A2(registers);
          break;
        default:
          return;
      }
    }

    //---------------------------------------------------------------//
    // No PREFIX
    //---------------------------------------------------------------//

    void Log_EX_AF_A2(Z80Registers& registers){
      std::cout << std::setw(7) << std::setfill(' ') << "A: " 
        << std::setw(2) << "0x" << std::setw(2) << std::setfill('0')
                << (static_cast<unsigned>(registers.a1) & 0xFF) << '\n';
      std::cout << std::setw(7) << std::setfill(' ') << "F: " 
        << std::setw(2) << "0x" << std::setw(2) << std::setfill('0')
        << (static_cast<unsigned>(registers.f1) & 0xFF) << '\n';
      std::cout << std::setw(7) << std::setfill(' ') << "A2: " 
        << std::setw(2) << "0x" << std::setw(2) << std::setfill('0')
        << (static_cast<unsigned>(registers.a2) & 0xFF) << '\n';
      std::cout << std::setw(7) << std::setfill(' ') << "F2: " 
        << std::setw(2) << "0x" << std::setw(2) << std::setfill('0')
        << (static_cast<unsigned>(registers.f2) & 0xFF) << '\n';
      std::cout << std::setw(7) << std::setfill(' ') << "AF1: " 
        << std::setw(2) << "0x" << std::setw(4) << std::setfill('0')
        << (static_cast<unsigned>(registers.af1) & 0xFFFF) << '\n';
      std::cout << std::setw(7) << std::setfill(' ') << "AF2: " 
        << std::setw(2) << "0x" << std::setw(4) << std::setfill('0')
        << (static_cast<unsigned>(registers.af2) & 0xFFFF) << '\n';
      std::cout << "----------" << "\n";
    }
};

}

#endif
