#include <catch2/catch_test_macros.hpp>
#include <cstdint>

#include "cpu/debugz80.hpp"
#include "48k/vram_utils.hpp"

TEST_CASE( "tests for 48k memory system screen", "[vram]" ) {

  SECTION("pixel coordinates"){
    // see if horizontal spans correctly
    for(int i = 0; i < 8; i++){
      const auto[x, y] = Trpp::PixelCoordinates(i, 0);
      std::uint16_t coordinate = Trpp::CoordinateAddress(x, y);
      REQUIRE(coordinate == 0x4000);
    }
  }

  // Vertical test is hard because of the transposition
  SECTION("Checks vertical for correctness"){
    for(int i = 0; i < 8; i++){
      const auto[x, y] = Trpp::PixelCoordinates(0, i);
      std::uint16_t coordinate = Trpp::CoordinateAddress(x, y);
      REQUIRE(coordinate == 0x4000 + 32*i);
    }
  }

  // attribute addresses:
  // 0x5800 - 0x581f = first line of attributes (should span 8 veritcal and 8 horizontal pxiels)
  // 0x5820 - 0x583f = second line of attbs etc

  // formula should be:
  // 0x5800 + ((y/8))*0x20 +  x / 8   x, y >= 0, x < 256, y < 192

  SECTION( "vram attribute coordinate addresses (0, 0)" ) {
    // see if horizontal spans correctly
    for(int i = 0; i < 8; i++){
      const auto[x, y] = Trpp::PixelCoordinates(i, 0);
      std::uint16_t coordinate = Trpp::AttributeAddress(x, y);
      REQUIRE(coordinate == 0x5800);
    }

    // see if vertical is correct
    for(int i = 0; i < 8; i++){
      const auto[x, y] = Trpp::PixelCoordinates(0, i);
      std::uint16_t coordinate = Trpp::AttributeAddress(x, y);
      REQUIRE(coordinate == 0x5800);
    }
  }

  SECTION( "vram attribute coordinate addresses (8, 0)" ) {
    // see if horizontal spans correctly
    for(int i = 0; i < 8; i++){
      const auto[x, y] = Trpp::PixelCoordinates(8 + i, 0);
      std::uint16_t coordinate = Trpp::AttributeAddress(x, y);
      REQUIRE(coordinate == 0x5801);
    }

    // see if vertical is correct
    for(int i = 0; i < 8; i++){
      const auto[x, y] = Trpp::PixelCoordinates(8, i);
      std::uint16_t coordinate = Trpp::AttributeAddress(x, y);
      REQUIRE(coordinate == 0x5801);
    }
  }

  // formula should be:
  // 0x5800 + ((y/8))*0x20 +  x / 8   x, y >= 0, x < 256, y < 192
  SECTION( "vram attribute coordinate addresses (16, 32)" ) {
    // see if horizontal spans correctly
    for(int i = 0; i < 8; i++){
      const auto[x, y] = Trpp::PixelCoordinates(16 + i, 32);
      std::uint16_t coordinate = Trpp::AttributeAddress(x, y);
      REQUIRE(coordinate == 0x5882);
    }

    // see if vertical is correct
    for(int i = 0; i < 8; i++){
      const auto[x, y] = Trpp::PixelCoordinates(16, 32 + i);
      std::uint16_t coordinate = Trpp::AttributeAddress(x, y);
      REQUIRE(coordinate == 0x5882);
    }
  }
}
