#ifndef CPU_IOSPACE_HPP
#define CPU_IOSPACE_HPP

// abstraction class that represents the interface to ioports from the
// z80 cpu. The Iospace is a collection of ioports.
//
// Allows the z80 to assign different ports, and thus it contains an 
// array of non owning pointers

#include <array>
#include <cstdint>

#include "io/ioport.hpp"

namespace Trpp::CPU{

  class IoSpace{
    static inline constexpr std::uint16_t NUM_IOPORTS = 256;
    public:
      //-------------------------------------------------------------
      //  Lifetime
      //-------------------------------------------------------------

      IoSpace(){
        for(auto port: m_buffer){
          port = nullptr;
        };
      }

      //-------------------------------------------------------------
      //  Configurations
      //-------------------------------------------------------------

      void SetPort(std::uint8_t address, IO::IoPort& src) noexcept{
        m_buffer[address] = &src;
      }

      void RemovePort(std::uint8_t address) noexcept{
        m_buffer[address] = nullptr;
      }

      //-------------------------------------------------------------
      //  Operator Overloads
      //-------------------------------------------------------------

      IO::IoPort& operator[](std::uint8_t address){
        return *m_buffer[address];
      }

      const IO::IoPort& operator[](std::uint8_t address) const{
        return *m_buffer[address];
      }

    private:
      std::array<IO::IoPort*, NUM_IOPORTS> m_buffer;
  };
}

#endif
