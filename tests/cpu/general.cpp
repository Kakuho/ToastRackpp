#include <catch2/catch_test_macros.hpp>
#include "cpu/debugz80.hpp"
#include "cpu/z80registers.hpp"

TEST_CASE( "constructor cases", "[cpu_ctor]" ) {
  SECTION( "default ctor means zero registers" ) {
    Trpp::CPU::DebugZ80 cpu;
    REQUIRE(cpu.RegistersAllZero() == true);
  }
}

TEST_CASE("z80register members", "[z80registers]"){
  SECTION( "z80register.operator=()" ) {
    Trpp::CPU::Z80RegisterPair reg;
    reg = 0x1234;
    REQUIRE(reg.high == 0x12);
    REQUIRE(reg.low == 0x34);
    REQUIRE(reg == 0x1234);
  }
}
