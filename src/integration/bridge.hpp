#include <iostream>
#include <bitset>

#include "ijob.hpp"
#include "48k/zxmemory48k.hpp"
#include "cpu/debugz80.hpp"
#include "cpu/z80bridge.hpp"

namespace integ{

  inline IJob testBridge{"test bridge", 
    [](){
      using namespace trpp;
      trpp::ZxMemory48K mem{0x11, 0x12, 0x13, 0x14};
      trpp::Z80Bridge bridge{&mem};
      bridge.Step();
    }
  };
}
