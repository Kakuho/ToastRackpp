#include <map>
#include <cstdint>
#include <iostream>

#include "dd_prefix_ops.hpp"

namespace dism::dd_prefix{

  inline std::map<std::uint8_t, DDFDPrefixOperation> table{
    {0x09, OPx09},
    //---------------------------------------------------------------//
    {0x19, OPx19},
    //---------------------------------------------------------------//
    {0x21, OPx21},
    {0x22, OPx22},
    {0x23, OPx23},
    {0x29, OPx29},
    {0x2a, OPx2a},
    {0x2b, OPx2b},
    //---------------------------------------------------------------//
    {0x34, OPx34},
    {0x35, OPx35},
    {0x36, OPx36},
    {0x39, OPx39},
    //---------------------------------------------------------------//
    {0x46, OPx46},
    {0x4e, OPx4e},
    //---------------------------------------------------------------//
    {0x56, OPx56},
    {0x5e, OPx5e},
    //---------------------------------------------------------------//
    {0x66, OPx66},
    {0x6E, OPx6e},
    //---------------------------------------------------------------//
    {0x70, OPx70},
    {0x71, OPx71},
    {0x72, OPx72},
    {0x73, OPx73},
    {0x74, OPx74},
    {0x75, OPx75},
    {0x77, OPx77},
    {0x7E, OPx7e},
    //---------------------------------------------------------------//
    {0x86, OPx86},
    {0x8e, OPx8e},
    //---------------------------------------------------------------//
    {0x96, OPx96},
    {0x9E, OPx9e},
    //---------------------------------------------------------------//
    {0xa6, OPxa6},
    {0xae, OPxae},
    //---------------------------------------------------------------//
    {0xb6, OPxb6},
    {0xbe, OPxbe},
    //---------------------------------------------------------------//
    {0xe1, OPxe1},
    {0xe3, OPxe3},
    {0xe6, OPxe6},
    {0xe9, OPxe9},
    //---------------------------------------------------------------//
    {0xf9, OPxf9}
  };

} // dism::no_prefix
