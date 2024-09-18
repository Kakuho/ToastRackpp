#include <catch2/catch_test_macros.hpp>
#include "cpu/debugz80.hpp"
#include "48k/zxmemory48k.hpp"
#include "cassert"

TEST_CASE( "tests for 48k memory system", "[48kmemory]" ) {

  SECTION( "test list initialisation" ) {
    trpp::ZxMemory48K memory{11, 12, 13, 14, 15, 16};
    REQUIRE(memory[0] == 11);
    REQUIRE(memory[1] == 12);
    REQUIRE(memory[2] == 13);
    REQUIRE(memory[3] == 14);
    REQUIRE(memory[4] == 15);
    REQUIRE(memory[5] == 16);
  }

}
