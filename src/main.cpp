#include <iostream>
#include <cassert>
#include "48k/cpu/z80.hpp"
#include "48k/cpu/instruction.hpp"
#include "integration/loader.hpp"

int main(){
  integ::testZ80Loader();
  integ::testLoaderTetris();
}
