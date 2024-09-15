#ifndef Z80LOADER_ENUMS_HPP  
#define Z80LOADER_ENUMS_HPP

// Enums for the Z80 File Loader
//
// Reference: https://worldofspectrum.org/faq/reference/z80format.htm

#include <cstdint>

namespace Trpp::Loader{

// we could bit pack z80file type || ver2 sys / ver3 sys information
// together

enum class Z80FileVersion: std::uint8_t{
  ver1, ver2, ver3
};

enum class Ver1SystemType: std::uint8_t{
  foureightk
};

enum class Ver2SystemType: std::uint8_t{
  foureightk = 0,
  foureightInterface1 = 1,
  samram = 2,
  onetwoeightk = 3,
  onetwoeightkInterface1 = 4
};

enum class Ver3SystemType: std::uint8_t{
  foureightk = 0,
  foureightInterface1 = 1,
  samram = 2,
  foureightkMgt = 3,
  onetwoeightk = 4,
  onetwoeightkInterface1 = 5,
  onetwoeightkMgt = 6
};

} // namespace trpp::loader

#endif
