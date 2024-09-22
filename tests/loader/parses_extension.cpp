#include <catch2/catch_test_macros.hpp>
#include <cassert>
#include <string>

#include "loader/utils.hpp"

TEST_CASE("Loader Utility Extension tests", "[parses_extension]" ) {

  SECTION("parses .z80") {
    using namespace Trpp::Loader;
    std::string filename = "hello.z80";
    Extension extension = ParseExtension(filename);
    REQUIRE(extension == Extension::Z80);
  }

}
