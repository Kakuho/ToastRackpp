#include <catch2/catch_test_macros.hpp>
#include "cpu/debugz80.hpp"
#include "48k/zxmemory48k.hpp"
#include "cassert"


TEST_CASE( "ld_r_ixd (load mem[ix + d] to register) example", "[ld_r_ixd_ex]" ) {
  Trpp::CPU::DebugZ80 cpu;
  Trpp::ZxMemory48K mem;
  cpu.ConnectMemory(&mem);
  assert(cpu.RegistersAllZero() == true);

  SECTION( "ld_r_ixd - page 90 example" ) {
    // set up
    cpu.SetIX(0x25AF);
    std::int8_t displacement = 0x19;
    mem[cpu.GetIX() + displacement] = 0x39;
    assert(mem[0x25AF + 0x19] = 0x39);
    // instruction invocation
    cpu.LD_r_ixd(0b000, 0x19);
    REQUIRE( cpu.GetB1() == 0x39 );
  }
}

/*
TEST_CASE( "ld_r_ixd (load mem[ix + d] to register) positive displacement cases ", "[ld_r_ixd_positive]" ) {
  Trpp::CPU::DebugZ80 cpu;
  Trpp::ZxMemory48K mem;
  cpu.ConnectMemory(&mem);
  assert(cpu.RegistersAllZero() == true);

  SECTION( "ld_r_hl (a, negative)" ) {
    // setup
    cpu.SetIX(0x25AF);
    std::int8_t displacement = 0x19;
    mem[cpu.GetIX() + displacement] = 0x39;
    assert(mem[0x25AF + 0x19] = 0x39);
    cpu.LD_r_hl(0b111);
    REQUIRE( cpu.GetA1() == 0x10 );
  }

  SECTION( "ld_r_hl (c)" ) {
    cpu.LD_r_hl(0b001);
    REQUIRE( cpu.GetC1() == 0x10 );
  }

  SECTION( "ld_r_hl (e)" ) {
    cpu.LD_r_hl(0b011);
    REQUIRE( cpu.GetE1() == 0x10 );
  }

  SECTION( "ld_r_hl (l)" ) {
    cpu.LD_r_hl(0b101);
    REQUIRE( cpu.GetL1() == 0x10 );
  }
}
*/
