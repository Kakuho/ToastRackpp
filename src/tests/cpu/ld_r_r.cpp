#include <catch2/catch_test_macros.hpp>
#include "cpu/debugz80.hpp"
#include "cassert"


TEST_CASE( "ld_r_r cases", "[ld_r_r]" ) {
  trpp::DebugZ80 cpu;
  assert(cpu.RegistersAllZero() == true);

  //---------------------------------------------------------------//
  // a as destination
  //---------------------------------------------------------------//

  SECTION( "ld_r_r (a, a)" ) {
    cpu.SetA1(0x24);
    cpu.SetA1(0x66);
    cpu.LD_r_r(0b111, 0b111);
    REQUIRE( cpu.GetA1() == 0x66 );
  }

  SECTION( "ld_r_r (a, b)" ) {
    cpu.SetA1(0x24);
    cpu.SetB1(0x66);
    cpu.LD_r_r(0b111, 0b000);
    REQUIRE( cpu.GetA1() == 0x66 );
  }

  SECTION( "ld_r_r (a, c)" ) {
    cpu.SetA1(0x24);
    cpu.SetC1(0x66);
    cpu.LD_r_r(0b111, 0b001);
    REQUIRE( cpu.GetA1() == 0x66 );
  }

  SECTION( "ld_r_r (a, d)" ) {
    cpu.SetA1(0x24);
    cpu.SetD1(0x66);
    cpu.LD_r_r(0b111, 0b010);
    REQUIRE( cpu.GetA1() == 0x66 );
  }

  SECTION( "ld_r_r (a, e)" ) {
    cpu.SetA1(0x24);
    cpu.SetE1(0x66);
    cpu.LD_r_r(0b111, 0b011);
    REQUIRE( cpu.GetA1() == 0x66 );
  }

  SECTION( "ld_r_r (a, h)" ) {
    cpu.SetA1(0x24);
    cpu.SetH1(0x66);
    cpu.LD_r_r(0b111, 0b100);
    REQUIRE( cpu.GetA1() == 0x66 );
  }

  SECTION( "ld_r_r (a, l)" ) {
    cpu.SetA1(0x24);
    cpu.SetL1(0x66);
    cpu.LD_r_r(0b111, 0b101);
    REQUIRE( cpu.GetA1() == 0x66 );
  }


  //---------------------------------------------------------------//
  // b as destination
  //---------------------------------------------------------------//

  SECTION( "ld_r_r (b, a)" ) {
    cpu.SetB1(0x24);
    cpu.SetA1(0x66);
    cpu.LD_r_r(0b000, 0b111);
    REQUIRE( cpu.GetB1() == 0x66 );
  }

  SECTION( "ld_r_r (b, b)" ) {
    cpu.SetB1(0x24);
    cpu.SetB1(0x66);
    cpu.LD_r_r(0b000, 0b000);
    REQUIRE( cpu.GetB1() == 0x66 );
  }

  SECTION( "ld_r_r (b, c)" ) {
    cpu.SetB1(0x24);
    cpu.SetC1(0x66);
    cpu.LD_r_r(0b000, 0b001);
    REQUIRE( cpu.GetB1() == 0x66 );
  }

  SECTION( "ld_r_r (b, d)" ) {
    cpu.SetB1(0x24);
    cpu.SetD1(0x66);
    cpu.LD_r_r(0b000, 0b010);
    REQUIRE( cpu.GetB1() == 0x66 );
  }

  SECTION( "ld_r_r (b, e)" ) {
    cpu.SetB1(0x24);
    cpu.SetE1(0x66);
    cpu.LD_r_r(0b000, 0b011);
    REQUIRE( cpu.GetB1() == 0x66 );
  }

  SECTION( "ld_r_r (b, h)" ) {
    cpu.SetB1(0x24);
    cpu.SetH1(0x66);
    cpu.LD_r_r(0b000, 0b100);
    REQUIRE( cpu.GetB1() == 0x66 );
  }

  SECTION( "ld_r_r (b, l)" ) {
    cpu.SetB1(0x24);
    cpu.SetL1(0x66);
    cpu.LD_r_r(0b000, 0b101);
    REQUIRE( cpu.GetB1() == 0x66 );
  }

  //---------------------------------------------------------------//
  // c as destination
  //---------------------------------------------------------------//

  SECTION( "ld_r_r (c, a)" ) {
    cpu.SetC1(0x24);
    cpu.SetA1(0x66);
    cpu.LD_r_r(0b001, 0b111);
    REQUIRE( cpu.GetC1() == 0x66 );
  }


  SECTION( "ld_r_r (c, b)" ) {
    cpu.SetC1(0x24);
    cpu.SetB1(0x66);
    cpu.LD_r_r(0b001, 0b000);
    REQUIRE( cpu.GetC1() == 0x66 );
  }

  SECTION( "ld_r_r (c, c)" ) {
    cpu.SetC1(0x24);
    cpu.SetC1(0x66);
    cpu.LD_r_r(0b001, 0b001);
    REQUIRE( cpu.GetC1() == 0x66 );
  }

  SECTION( "ld_r_r (c, d)" ) {
    cpu.SetC1(0x24);
    cpu.SetD1(0x66);
    cpu.LD_r_r(0b001, 0b010);
    REQUIRE( cpu.GetC1() == 0x66 );
  }

  SECTION( "ld_r_r (c, e)" ) {
    cpu.SetC1(0x24);
    cpu.SetE1(0x66);
    cpu.LD_r_r(0b001, 0b011);
    REQUIRE( cpu.GetC1() == 0x66 );
  }

  SECTION( "ld_r_r (c, h)" ) {
    cpu.SetC1(0x24);
    cpu.SetH1(0x66);
    cpu.LD_r_r(0b001, 0b100);
    REQUIRE( cpu.GetC1() == 0x66 );
  }

  SECTION( "ld_r_r (c, l)" ) {
    cpu.SetC1(0x24);
    cpu.SetL1(0x66);
    cpu.LD_r_r(0b001, 0b101);
    REQUIRE( cpu.GetC1() == 0x66 );
  }

  //---------------------------------------------------------------//
  // d as destination
  //---------------------------------------------------------------//

  SECTION( "ld_r_r (d, a)" ) {
    cpu.SetD1(0x24);
    cpu.SetA1(0x66);
    cpu.LD_r_r(0b010, 0b111);
    REQUIRE( cpu.GetD1() == 0x66 );
  }

  SECTION( "ld_r_r (d, b)" ) {
    cpu.SetD1(0x24);
    cpu.SetB1(0x66);
    cpu.LD_r_r(0b010, 0b000);
    REQUIRE( cpu.GetD1() == 0x66 );
  }

  SECTION( "ld_r_r (d, c)" ) {
    cpu.SetD1(0x24);
    cpu.SetC1(0x66);
    cpu.LD_r_r(0b010, 0b001);
    REQUIRE( cpu.GetD1() == 0x66 );
  }

  SECTION( "ld_r_r (d, d)" ) {
    cpu.SetD1(0x24);
    cpu.SetD1(0x66);
    cpu.LD_r_r(0b010, 0b010);
    REQUIRE( cpu.GetD1() == 0x66 );
  }

  SECTION( "ld_r_r (d, e)" ) {
    cpu.SetD1(0x24);
    cpu.SetE1(0x66);
    cpu.LD_r_r(0b010, 0b011);
    REQUIRE( cpu.GetD1() == 0x66 );
  }

  SECTION( "ld_r_r (d, h)" ) {
    cpu.SetD1(0x24);
    cpu.SetH1(0x66);
    cpu.LD_r_r(0b010, 0b100);
    REQUIRE( cpu.GetD1() == 0x66 );
  }

  SECTION( "ld_r_r (d, l)" ) {
    cpu.SetD1(0x24);
    cpu.SetL1(0x66);
    cpu.LD_r_r(0b010, 0b101);
    REQUIRE( cpu.GetD1() == 0x66 );
  }
}
