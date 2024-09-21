#ifndef IO_IOPORT_HPP
#define IO_IOPORT_HPP

// Reference: The ZX Spectrum ULA ch19, ch3

#include <cstdint>

namespace trpp{

class IoPort{

  private:
    std::uint8_t value;
};

} // namespace trpp

#endif
