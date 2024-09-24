#include <catch2/catch_test_macros.hpp>
#include <vector>

#include "loader/z80loader/z80loader.hpp"
#include "loader/z80loader/z80decompressor.hpp"
#include "cassert"

TEST_CASE("tests to see if z80decompressor can decompress a giant chunk", "[chunkbig]" ) {

  SECTION("big chunking test1") {
    Trpp::Loader::Z80Decompressor decomp;
    std::vector<std::uint8_t> memory{
        0x00, 0x05,
        0x00,
        0xED, 0xED, 0x03, 0xED, 0xAB, // 8
        0x00, 0x04,
        0x01,
        0xAB, 0xAB, 0xAB, 0xAB
    };
    auto output = decomp.DecompressV23(std::move(memory));
    // chunk with index 0
    REQUIRE(output[0x00].size() == 4);
    REQUIRE(output[0x00][0] == 0xED);
    REQUIRE(output[0x00][1] == 0xED);
    REQUIRE(output[0x00][2] == 0xED);
    REQUIRE(output[0x00][3] == 0xAB);
    // chunk with index 1
    REQUIRE(output[0x01].size() == 4);
    REQUIRE(output[0x01][0] == 0xAB);
    REQUIRE(output[0x01][1] == 0xAB);
    REQUIRE(output[0x01][2] == 0xAB);
    REQUIRE(output[0x01][3] == 0xAB);
  }
}
