#include <iostream>
#include <cassert>

#include "cpu/z80.hpp"
#include "cpu/instruction_tables/instruction_db.hpp"
#include "integration/loader.hpp"
#include "integration/edinstruction.hpp"


int main(){
  integ::testZ80Loader();
  integ::testLoaderTetris();
  trpp::CycleEntry{10, trpp::TCycleBreakdown{10, 2, 3}};
  integ::testEX_AF_AF2();
  integ::testLD_dd_nn();
}
