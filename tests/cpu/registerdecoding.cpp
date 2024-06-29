#include <catch2/catch_test_macros.hpp>
#include "cpu/debugz80.hpp"
#include "48k/zxmemory48k.hpp"

TEST_CASE( "8 bit register table cases", "[register_table]" ) {
  trpp::DebugZ80 cpu;
  assert(cpu.RegistersAllZero() == true);

  SECTION( "selects b" ) {
    cpu.registerTable(0b0) = 0x67;
    REQUIRE(cpu.GetB1() == 0x67);
  }

  SECTION( "selects c" ) {
    cpu.registerTable(0b1) = 0x67;
    REQUIRE(cpu.GetC1() == 0x67);
  }

  SECTION( "selects d" ) {
    cpu.registerTable(0b10) = 0x67;
    REQUIRE(cpu.GetD1() == 0x67);
  }

  SECTION( "selects e" ) {
    cpu.registerTable(0b11) = 0x67;
    REQUIRE(cpu.GetE1() == 0x67);
  }

  SECTION( "selects h" ) {
    cpu.registerTable(0b100) = 0x67;
    REQUIRE(cpu.GetH1() == 0x67);
  }

  SECTION( "selects l" ) {
    cpu.registerTable(0b101) = 0x67;
    REQUIRE(cpu.GetL1() == 0x67);
  }

  SECTION( "selects (hl)" ) {
    trpp::ZxMemory48K memory;
    cpu.ConnectMemory(& memory);
    cpu.registerTable(0b110) = 0x67;
    REQUIRE(memory[cpu.GetHL1()] == 0x67);
  }

  SECTION( "selects a" ) {
    cpu.registerTable(0b111) = 0x67;
    REQUIRE(cpu.GetA1() == 0x67);
  }
}

TEST_CASE( "16 bit register pair table cases", "[register_table]" ) {
  trpp::DebugZ80 cpu;
  assert(cpu.RegistersAllZero() == true);

  SECTION( "selects BC" ) {
    cpu.registerPairSPTable(0b00) = 0x67;
    REQUIRE(cpu.GetBC1() == 0x67);
    cpu.registerPairAFTable(0b00) = 0x43;
    REQUIRE(cpu.GetBC1() == 0x43);
  }

  SECTION( "selects DE" ) {
    cpu.registerPairSPTable(0b01) = 0x67;
    REQUIRE(cpu.GetDE1() == 0x67);
    cpu.registerPairAFTable(0b01) = 0x43;
    REQUIRE(cpu.GetDE1() == 0x43);
  }

  SECTION( "selects HL" ) {
    cpu.registerPairSPTable(0b10) = 0x67;
    REQUIRE(cpu.GetHL1() == 0x67);
    cpu.registerPairAFTable(0b10) = 0x43;
    REQUIRE(cpu.GetHL1() == 0x43);
  }

  SECTION( "selects SP" ) {
    cpu.registerPairSPTable(0b11) = 0x67;
    REQUIRE(cpu.GetSP() == 0x67);
  }

  SECTION( "selects AF" ) {
    cpu.registerPairAFTable(0b11) = 0x67;
    REQUIRE(cpu.GetAF1() == 0x67);
  }
}
