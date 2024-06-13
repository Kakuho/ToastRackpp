#include <iostream>
#include <bitset>
#include "ijob.hpp"
#include "loader/taploader.hpp"
#include "loader/z80loader.hpp"
#include "48k/memory48k.hpp"

namespace integ{

  inline IJob testTapLoader{"test .tap loader", 
    [](){
      using namespace trpp;
      TapLoader tl{"../assets/tap/hero.tap"};
      //tl.PrintRawBytes();
      std::cout << "ayo!" << '\n';
      //tl.PrintRawBytes(0x13 + 2);
      tl.PrintChunks();
    }
  };

  inline IJob testZ80Loader{"test .z80 loader", 
    [](){
      using namespace trpp;
      Z80Loader zl{"../assets/z80/CALIPSE.Z80"}; // note CALIPSE.Z80 is not compressed
      zl.PrintRawBytes(35);
      zl.PrintHeader();
      std::cout << std::bitset<8>(zl.ParseRefreshRegister()).to_ulong() << '\n';
      std::cout << "ayo!" << '\n';
    }
  };

  inline IJob testLoaderTetris{"test tetris loader", 
    [](){
      using namespace trpp;
      Z80Loader zl{"../assets/z80/TETRIS.Z80"}; // note CALIPSE.Z80 is not compressed
      zl.PrintRawBytes(35);
      zl.PrintSpectrumModel();
    }
  };
}
