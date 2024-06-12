#include <iostream>
#include <bitset>
#include "./../loader/taploader.hpp"
#include "./../loader/z80loader.hpp"
#include "./../48k/48kmemory.hpp"

namespace integ{
  inline void testTapLoader(){
    using namespace trpp;
    TapLoader tl{"../assets/tap/hero.tap"};
    //tl.PrintRawBytes();
    std::cout << "ayo!" << '\n';
    //tl.PrintRawBytes(0x13 + 2);
    tl.PrintChunks();
  }

  inline void testZ80Loader(){
    using namespace trpp;
    Z80Loader zl{"../assets/z80/CALIPSE.Z80"}; // note CALIPSE.Z80 is not compressed
    zl.PrintRawBytes(35);
    zl.PrintHeader();
    std::cout << std::bitset<8>(zl.ParseRefreshRegister()).to_ulong() << '\n';
    std::cout << "ayo!" << '\n';
  }

  inline void testZ80LoaderMachineModel(){
    std::cout << "--------------------------------\nIntegration Prodcedure Start\n\n";
    using namespace trpp;
    Z80Loader zl{"../assets/z80/CALIPSE.Z80"}; // note CALIPSE.Z80 is not compressed
    zl.PrintRawBytes(35);
    zl.PrintSpectrumModel();
    std::cout << "\nIntegration Prodcedure End\n--------------------------------\n";
  }

  inline void testZ80LoaderMachineModelTetris(){
    std::cout << "--------------------------------\nIntegration Prodcedure Start\n\n";
    using namespace trpp;
    Z80Loader zl{"../assets/z80/TETRIS.Z80"}; // note CALIPSE.Z80 is not compressed
    zl.PrintRawBytes(35);
    zl.PrintSpectrumModel();
    std::cout << "\nIntegration Prodcedure End\n--------------------------------\n";
  }
}
