#ifndef INSTRUCTION_DB_HPP
#define INSTRUCTION_DB_HPP

// includes basic information regarding instructions including number of 
// cycles each takes, 

#include <cstdint>
#include <unordered_map>
#include <optional>

namespace trpp{

  enum class FlagAffects: std::uint8_t{
    c =  1,
    n =  2,
    p =  4,
    v =  4,
    h = 16,
    z = 64,
    s = 128,
  };

  constexpr FlagAffects operator|(FlagAffects lhs, FlagAffects rhs){
    return static_cast<FlagAffects>(static_cast<std::uint8_t>(lhs) | static_cast<std::uint8_t>(rhs));
  }

  struct InstructionEntry{
    using flagbitmask = std::uint8_t;
    std::uint8_t tcycles;
    std::uint8_t mcycles;
    FlagAffects  flags;
  };

  using TCycleBreakdown = std::array<std::optional<std::uint8_t>, 4>;

  struct CycleEntry{
    CycleEntry(std::uint8_t mcycles, TCycleBreakdown tcycles):
      mcycles{mcycles}, tcycles{tcycles}{}
    std::uint8_t mcycles;
    std::uint8_t tcycleBitmap;
    TCycleBreakdown tcycles{};
  };

  inline std::unordered_map<std::uint8_t, InstructionEntry> opcode{
    //  opcode |                    t cycles   | m cycles  | flags
    {   0x00     , InstructionEntry{1,           2,          FlagAffects::c}},
    {   0x00     , InstructionEntry{1,           2,          FlagAffects::c}}
  };
}

#endif
