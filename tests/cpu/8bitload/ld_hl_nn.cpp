#include <catch2/catch_test_macros.hpp>
#include "cpu/debugz80.hpp"
#include "48k/zxmemory48k.hpp"
#include "cassert"

TEST_CASE( "ld_hl_n (load n to mem[hl]) cases (HL = 0x50)", "[ld_hl_n_0x50]" ) {
  trpp::DebugZ80 cpu;
  trpp::ZxMemory48K mem;
  cpu.ConnectMemory(&mem);
  assert(cpu.RegistersAllZero() == true);
  cpu.SetHL1(0x50);
  assert(cpu.GetHL1() == 0x50);
  assert(mem[cpu.GetHL1()] == 0x0);

  SECTION( "ld_hl_n (n = 0x46)" ) {
    cpu.LD_hl_n(0x46);
    REQUIRE( mem[cpu.GetHL1()] == 0x46);
  }

  SECTION( "ld_hl_n (n = 0x89)" ) {
    cpu.LD_hl_r(0x89);
    REQUIRE( mem[cpu.GetHL1()] == 0x99 );
  }

  SECTION( "ld_hl_n (n = 0x00)" ) {
    cpu.LD_hl_n(0);
    REQUIRE( mem[cpu.GetHL1()] == 0);
  }

  SECTION( "ld_hl_n (n = 0xFF)" ) {
    cpu.LD_hl_r(0xFF);
    REQUIRE( mem[cpu.GetHL1()] == 0xFF);
  }
}

TEST_CASE( "ld_hl_n (load n to mem[hl]) cases (HL = 0x83)", "[ld_hl_n_0x50]" ) {
  trpp::DebugZ80 cpu;
  trpp::ZxMemory48K mem;
  cpu.ConnectMemory(&mem);
  assert(cpu.RegistersAllZero() == true);
  cpu.SetHL1(0x83);
  assert(cpu.GetHL1() == 0x83);
  assert(mem[cpu.GetHL1()] == 0x0);

  SECTION( "ld_hl_n (n = 0x46)" ) {
    cpu.LD_hl_n(0x46);
    REQUIRE( mem[cpu.GetHL1()] == 0x46);
  }

  SECTION( "ld_hl_n (n = 0x89)" ) {
    cpu.LD_hl_r(0x89);
    REQUIRE( mem[cpu.GetHL1()] == 0x99 );
  }

  SECTION( "ld_hl_n (n = 0x00)" ) {
    cpu.LD_hl_n(0);
    REQUIRE( mem[cpu.GetHL1()] == 0);
  }

  SECTION( "ld_hl_n (n = 0xFF)" ) {
    cpu.LD_hl_r(0xFF);
    REQUIRE( mem[cpu.GetHL1()] == 0xFF);
  }
}

TEST_CASE( "ld_hl_n (load n to mem[hl]) cases (HL = 0x0)", "[ld_hl_n_0x50]" ) {
  trpp::DebugZ80 cpu;
  trpp::ZxMemory48K mem;
  cpu.ConnectMemory(&mem);
  assert(cpu.RegistersAllZero() == true);
  cpu.SetHL1(0x0);
  assert(cpu.GetHL1() == 0x0);
  assert(mem[cpu.GetHL1()] == 0x0);

  SECTION( "ld_hl_n (n = 0x46)" ) {
    cpu.LD_hl_n(0x46);
    REQUIRE( mem[cpu.GetHL1()] == 0x46);
  }

  SECTION( "ld_hl_n (n = 0x89)" ) {
    cpu.LD_hl_r(0x89);
    REQUIRE( mem[cpu.GetHL1()] == 0x99 );
  }

  SECTION( "ld_hl_n (n = 0x00)" ) {
    cpu.LD_hl_n(0);
    REQUIRE( mem[cpu.GetHL1()] == 0);
  }

  SECTION( "ld_hl_n (n = 0xFF)" ) {
    cpu.LD_hl_r(0xFF);
    REQUIRE( mem[cpu.GetHL1()] == 0xFF);
  }
}
