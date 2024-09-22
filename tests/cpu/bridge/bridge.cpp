#include <catch2/catch_test_macros.hpp>
#include "cpu/debugz80.hpp"
#include "cpu/z80bridge.hpp"
#include "48k/zxmemory48k.hpp"
#include "cassert"
#include "cpu/z80.hpp"

TEST_CASE( "integration testing the cpu bridge", "[z80bridge]" ) {
  // ------------------------------------------------------ //
  // Set up
  // ------------------------------------------------------ //

  // the data
  Trpp::ZxMemory48K mem{0x11, 0x12, 0x13, 0x14};
  Trpp::CPU::Z80Bridge bridge{&mem};

  // ------------------------------------------------------ //
  // Tests
  // ------------------------------------------------------ //

  SECTION("the cpu does stepping :D"){
  stepping:
    bridge.Step();
  }

}
