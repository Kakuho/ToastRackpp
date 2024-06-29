#include <catch2/catch_test_macros.hpp>
#include "cpu/debugz80.hpp"
#include "48k/zxmemory48k.hpp"
#include "cassert"

TEST_CASE( "ld_r_hl (load mem[hl] to register) cases", "[ld_r_hl]" ) {
  trpp::DebugZ80 cpu;
  trpp::ZxMemory48K mem;
  cpu.ConnectMemory(&mem);
  assert(cpu.RegistersAllZero() == true);
  cpu.SetHL1(0x50);
  mem[cpu.GetHL1()] = 0x10;

  SECTION( "ld_r_hl (a)" ) {
    cpu.LD_r_hl(0b111);
    REQUIRE( cpu.GetA1() == 0x10 );
  }

  SECTION( "ld_r_hl (b)" ) {
    cpu.LD_r_hl(0b000);
    REQUIRE( cpu.GetB1() == 0x10 );
  }

  SECTION( "ld_r_hl (c)" ) {
    cpu.LD_r_hl(0b001);
    REQUIRE( cpu.GetC1() == 0x10 );
  }

  SECTION( "ld_r_hl (d)" ) {
    cpu.LD_r_hl(0b010);
    REQUIRE( cpu.GetD1() == 0x10 );
  }

  SECTION( "ld_r_hl (e)" ) {
    cpu.LD_r_hl(0b011);
    REQUIRE( cpu.GetE1() == 0x10 );
  }

  SECTION( "ld_r_hl (h)" ) {
    cpu.LD_r_hl(0b100);
    REQUIRE( cpu.GetH1() == 0x10 );
  }

  SECTION( "ld_r_hl (l)" ) {
    cpu.LD_r_hl(0b101);
    REQUIRE( cpu.GetL1() == 0x10 );
  }

}
