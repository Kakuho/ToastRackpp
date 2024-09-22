#include <catch2/catch_test_macros.hpp>
#include "cpu/debugz80.hpp"
#include "cassert"

TEST_CASE( "ld_r_n (load immediate to register) cases", "[ld_r_n]" ) {
  Trpp::CPU::DebugZ80 cpu;
  assert(cpu.RegistersAllZero() == true);

  SECTION( "ld_r_n (a, 0x10)" ) {
    cpu.LD_r_n(0b111, 0x10);
    REQUIRE( cpu.GetA1() == 0x10 );
  }

  SECTION( "ld_r_n (b, 0xFF)" ) {
    cpu.LD_r_n(0b000, 0xFF);
    REQUIRE( cpu.GetB1() == 0xFF );
  }

  SECTION( "ld_r_n (d, 0x98)" ) {
    cpu.LD_r_n(0b010, 0x98);
    REQUIRE( cpu.GetD1() == 0x98 );
  }

  SECTION( "ld_r_n (e, 0x20)" ) {
    cpu.LD_r_n(0b011, 0x20);
    REQUIRE( cpu.GetE1() == 0x20 );
  }

  SECTION( "ld_r_n (h, 0x39)" ) {
    cpu.LD_r_n(0b100, 0x39);
    REQUIRE( cpu.GetH1() == 0x39 );
  }

  SECTION( "ld_r_r (l, 0x57)" ) {
    cpu.LD_r_n(0b101, 0x57);
    REQUIRE( cpu.GetL1() == 0x57 );
  }

}
