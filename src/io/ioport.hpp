#ifndef IO_IOPORT_HPP
#define IO_IOPORT_HPP

// Reference: The ZX Spectrum ULA ch19, ch3

#include <cstdint>

namespace Trpp::IO{

class IoPort{
  public:
    std::uint8_t value;
};

} // namespace Trpp::IO

#endif
