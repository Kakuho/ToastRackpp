#include <cstdint>

namespace trpp{

struct Z80FileInfoBitmap{
  // poc for system information being stored on a bitmap
  // first 2 bits encodes file version
  // next 4 bits equals sys type dependent on the file version
  // or even ignored
  std::uint8_t bitmap;
};

}
