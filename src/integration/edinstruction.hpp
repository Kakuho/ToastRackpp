#include "ijob.hpp"
#include "cpu/debugz80.hpp"
#include "iostream"

namespace integ{

inline IJob testEX_AF_AF2{"test EX_AF_AF2()", 
    [](){
      using namespace trpp;
      DebugZ80 cpu{};
      cpu.SetA1(0x45);
      cpu.EX_AF_AF2();
    }
};

inline IJob testLD_dd_nn{"test LD_dd_nn", 
    [](){
      using namespace trpp;
      DebugZ80 cpu{};
      cpu.SetA1(0x45);
      cpu.LD_dd_nn(0b01, 0xf0, 0xab);
    }
};

}
