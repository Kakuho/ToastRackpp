#include <iostream>
#include <cassert>

#include "cpu/z80.hpp"
#include "cpu/instruction_tables/instruction_db.hpp"
#include "integration/loader.hpp"
#include "integration/edinstruction.hpp"
#include "integration/bridge.hpp"

int main(){
  integ::testBridge();
}
