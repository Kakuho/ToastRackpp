#include <iostream>
#include <cassert>

#include "48k/zxmemory48k.hpp"
#include "cpu/z80.hpp"
#include "48k/spectrum48k.hpp"
#include "integration/loader.hpp"
#include "integration/edinstruction.hpp"
#include "integration/bridge.hpp"
#include "loader/z80loader/z80loader.hpp"

int main(){
  std::string filename{"./../assets/z80/TETRIS.z80"};
  Trpp::Loader::Z80Loader loader{ filename };
  Trpp::ZxMemory48K memory{};
  loader.Load(memory);
}
