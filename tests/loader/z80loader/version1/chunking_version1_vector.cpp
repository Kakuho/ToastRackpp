#include <catch2/catch_test_macros.hpp>
#include <vector>

#include "loader/z80loader/z80loader.hpp"
#include "loader/z80loader/z80decompressor.hpp"
#include "cassert"

TEST_CASE("tests for z80loader memory system VERSION 1", "[chunkvectorVer1]" ) {

  SECTION("chunking test1") {
    Trpp::Loader::Z80Decompressor decomp;
    std::vector<std::uint8_t> output = 
      decomp.DecompressV1(std::vector<std::uint8_t>{
        0xED, 0xED, 0x03, 0xED, 0xAB,
        0x00, 0xED, 0xED, 0x00
    });
    REQUIRE(output.size() == 4);
    REQUIRE(output[0] == 0xED);
    REQUIRE(output[1] == 0xED);
    REQUIRE(output[2] == 0xED);
    REQUIRE(output[3] == 0xAB);
  }

  SECTION("chunking test2 1 compressed block, 0xED 0xAB") {
    // 0xED 0xED 0x03 0xED 0xED 0xAB
    // should be 
    // 3*0xED 0xED 0xAB
    Trpp::Loader::Z80Decompressor decomp;
    std::vector<std::uint8_t> output = 
      decomp.DecompressV1(std::vector<std::uint8_t>{
        0xED, 0xED, 0x03, 0xED, 0xED, 0xAB,
        0x00, 0xED, 0xED, 0x00
    });
    REQUIRE(output.size() == 5);
    REQUIRE(output[0] == 0xED);
    REQUIRE(output[1] == 0xED);
    REQUIRE(output[2] == 0xED);
    REQUIRE(output[3] == 0xED);
    REQUIRE(output[4] == 0xAB);
  }

  SECTION("chunking test3 0xED 0xAB 1 compressed block") {
    Trpp::Loader::Z80Decompressor decomp;
    std::vector<std::uint8_t> output = 
      decomp.DecompressV1(std::vector<std::uint8_t>{
        0xED, 0xAB, 0xED, 0xED, 0x03, 0xED,
        0x00, 0xED, 0xED, 0x00
    });
    REQUIRE(output.size() == 5);
    REQUIRE(output[0] == 0xED);
    REQUIRE(output[1] == 0xAB);
    REQUIRE(output[2] == 0xED);
    REQUIRE(output[3] == 0xED);
    REQUIRE(output[4] == 0xED);
  }

  SECTION("chunking test4 2 compressed blocks") {
    // [0xED 0xED 0x03 0xED] [0xED 0xED 0x04 0xAB]
    // should be 
    // 3*0xED 4*0xAB
    Trpp::Loader::Z80Decompressor decomp;
    std::vector<std::uint8_t> output = 
      decomp.DecompressV1(std::vector<std::uint8_t>{
        0xED, 0xED, 0x03, 0xED, 0xED, 0xED, 0x04, 0xAB,
        0x00, 0xED, 0xED, 0x00
    });
    REQUIRE(output.size() == 7);
    REQUIRE(output[0] == 0xED);
    REQUIRE(output[1] == 0xED);
    REQUIRE(output[2] == 0xED);
    REQUIRE(output[3] == 0xAB);
    REQUIRE(output[4] == 0xAB);
    REQUIRE(output[5] == 0xAB);
    REQUIRE(output[6] == 0xAB);
  }

  SECTION("chunking test5 no compressed blocks") {
    Trpp::Loader::Z80Decompressor decomp;
    std::vector<std::uint8_t> output = 
      decomp.DecompressV1(std::vector<std::uint8_t>{
        0x12, 0x23, 0x34, 0x45, 0x56,
        0x00, 0xED, 0xED, 0x00
    });
    REQUIRE(output.size() == 5);
    REQUIRE(output[0] == 0x12);
    REQUIRE(output[1] == 0x23);
    REQUIRE(output[2] == 0x34);
    REQUIRE(output[3] == 0x45);
    REQUIRE(output[4] == 0x56);
  }
}
