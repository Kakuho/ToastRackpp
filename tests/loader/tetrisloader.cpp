#include <catch2/catch_test_macros.hpp>
#include "cpu/debugz80.hpp"
#include "48k/zxmemory48k.hpp"
#include "loader/z80loader/z80loader.hpp"
#include "cassert"

TEST_CASE("tests for 48k memory system", "[z80loader]" ) {

  SECTION("test initialisation") {
    trpp::ZxMemory48K memory;
    Trpp::Loader::Z80Loader loader{"tetris.z80"};
    loader.Load(memory);
  }

}
