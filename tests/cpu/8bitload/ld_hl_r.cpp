#include <catch2/catch_test_macros.hpp>
#include "cpu/debugz80.hpp"
#include "48k/zxmemory48k.hpp"
#include "cassert"

TEST_CASE( "ld_hl_r (load register to mem[hl]) cases (HL = 0x50)", "[ld_hl_r_0x50]" ) {
  Trpp::CPU::DebugZ80 cpu;
  Trpp::ZxMemory48K mem;
  cpu.ConnectMemory(&mem);
  assert(cpu.RegistersAllZero() == true);
  cpu.SetHL1(0x50);
  assert(cpu.GetHL1() == 0x50);

  SECTION( "ld_hl_r (a = 0x46)" ) {
    cpu.SetA1(0x46);
    cpu.LD_hl_r(0b111);
    REQUIRE( mem[cpu.GetHL1()] == 0x46);
  }

  SECTION( "ld_hl_r (c = 0x59)" ) {
    cpu.SetC1(0x59);
    cpu.LD_hl_r(0b001);
    REQUIRE( mem[cpu.GetHL1()] == 0x59 );
  }

  SECTION( "ld_hl_r (e = 0x39)" ) {
    cpu.SetE1(0x39);
    cpu.LD_hl_r(0b011);
    REQUIRE( mem[cpu.GetHL1()] == 0x39);
  }

  SECTION( "ld_hl_r (l = 0x99)" ) {
    cpu.SetL1(0x99);
    cpu.LD_hl_r(0b101);
    REQUIRE( mem[cpu.GetHL1()] == 0x99);
  }
}

TEST_CASE( "ld_hl_r (load register to mem[hl]) cases (HL = 0x90)", "[ld_hl_r_0x90]" ) {
  Trpp::CPU::DebugZ80 cpu;
  Trpp::ZxMemory48K mem;
  cpu.ConnectMemory(&mem);
  assert(cpu.RegistersAllZero() == true);
  cpu.SetHL1(0x90);
  assert(cpu.GetHL1() == 0x90);

  SECTION( "ld_hl_r (a = 0x46)" ) {
    cpu.SetA1(0x46);
    cpu.LD_hl_r(0b111);
    REQUIRE( mem[cpu.GetHL1()] == 0x46 );
  }

  SECTION( "ld_hl_r (c = 0x59)" ) {
    cpu.SetC1(0x59);
    cpu.LD_hl_r(0b001);
    REQUIRE( mem[cpu.GetHL1()] == 0x59 );
  }

  SECTION( "ld_hl_r (e = 0x39)" ) {
    cpu.SetE1(0x39);
    cpu.LD_hl_r(0b011);
    REQUIRE( mem[cpu.GetHL1()] == 0x39 );
  }

  SECTION( "ld_hl_r (l = 0x99)" ) {
    cpu.SetL1(0x99);
    cpu.LD_hl_r(0b101);
    REQUIRE( mem[cpu.GetHL1()] == 0x99 );
  }
}

TEST_CASE( "ld_hl_r (load register to mem[hl]) cases (HL = 0x00)", "[ld_hl_r_0x00]" ) {
  Trpp::CPU::DebugZ80 cpu;
  Trpp::ZxMemory48K mem;
  cpu.ConnectMemory(&mem);
  assert(cpu.RegistersAllZero() == true);
  cpu.SetHL1(0x00);
  assert(cpu.GetHL1() == 0x0);

  SECTION( "ld_hl_r (a = 0x46)" ) {
    cpu.SetA1(0x46);
    cpu.LD_hl_r(0b111);
    REQUIRE( mem[cpu.GetHL1()] == 0x46 );
  }

  SECTION( "ld_hl_r (c = 0x59)" ) {
    cpu.SetC1(0x59);
    cpu.LD_hl_r(0b001);
    REQUIRE( mem[cpu.GetHL1()] == 0x59 );
  }

  SECTION( "ld_hl_r (e = 0x39)" ) {
    cpu.SetE1(0x39);
    cpu.LD_hl_r(0b011);
    REQUIRE( mem[cpu.GetHL1()] == 0x39 );
  }

  SECTION( "ld_hl_r (l = 0x99)" ) {
    cpu.SetL1(0x99);
    cpu.LD_hl_r(0b101);
    REQUIRE( mem[cpu.GetHL1()] == 0x99 );
  }
}

TEST_CASE( "ld_hl_r (load register to mem[hl]) cases (HL = 0xFF)", "[ld_hl_r_0xFF]" ) {
  Trpp::CPU::DebugZ80 cpu;
  Trpp::ZxMemory48K mem;
  cpu.ConnectMemory(&mem);
  assert(cpu.RegistersAllZero() == true);
  cpu.SetHL1(0xFF);
  assert(cpu.GetHL1() == 0xFF);

  SECTION( "ld_hl_r (a = 0x46)" ) {
    cpu.SetA1(0x46);
    cpu.LD_hl_r(0b111);
    REQUIRE( mem[cpu.GetHL1()] == 0x46 );
  }

  SECTION( "ld_hl_r (c = 0x59)" ) {
    cpu.SetC1(0x59);
    cpu.LD_hl_r(0b001);
    REQUIRE( mem[cpu.GetHL1()] == 0x59 );
  }

  SECTION( "ld_hl_r (e = 0x39)" ) {
    cpu.SetE1(0x39);
    cpu.LD_hl_r(0b011);
    REQUIRE( mem[cpu.GetHL1()] == 0x39 );
  }

  SECTION( "ld_hl_r (l = 0x99)" ) {
    cpu.SetL1(0x99);
    cpu.LD_hl_r(0b101);
    REQUIRE( mem[cpu.GetHL1()] == 0x99 );
  }
}
