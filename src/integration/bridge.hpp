#include <iostream>
#include <bitset>

#include "ijob.hpp"
#include "48k/zxmemory48k.hpp"
#include "cpu/debugz80.hpp"
#include "cpu/z80bridge.hpp"

namespace Trpp::Integration{

  inline IJob testBridge{"test bridge", 
    [](){
      ZxMemory48K mem{0x11, 0x12, 0x13, 0x14};
      CPU::Z80Bridge bridge{&mem};
      bridge.Step();
    }
  };

} // namespace Trpp::Integration
