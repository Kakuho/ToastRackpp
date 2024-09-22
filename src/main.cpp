#include <iostream>
#include <cassert>

#include "cpu/z80.hpp"
#include "48k/spectrum48k.hpp"
#include "integration/loader.hpp"
#include "integration/edinstruction.hpp"
#include "integration/bridge.hpp"

int main(){
  Trpp::Spectrum48K system{};
  system.LoadFile("./../assets/z80/TETRIS.z80");
}
