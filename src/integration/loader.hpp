#include <iostream>
#include <bitset>
#include "./../loader/taploader.hpp"
#include "./../loader/z80loader.hpp"

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
    zl.PrintRawBytes(30);
    zl.PrintHeader();
    std::cout << std::bitset<8>(zl.ParseRefreshRegister()).to_ulong() << '\n';
    std::cout << "ayo!" << '\n';
  }
}
