#ifndef I_TABLE_NOPREFIX_HPP
#define I_TABLE_NOPREFIX_HPP

// NoPrefixTable is a LUT for instructions with no prefixes
//
// Reference:

#include <array>
#include <cstdint>
#include <cassert>

#include "enums/enums.hpp"

namespace trpp::instructions{

class NoPrefixTable{
  public:
    //-------------------------------------------------------------
    //  Constants
    //-------------------------------------------------------------

    static constexpr std::size_t TABLE_SIZE = 0xff;

    //-------------------------------------------------------------
    // lifetime
    //-------------------------------------------------------------

    // only provide construction semantics, no copying / moving
    NoPrefixTable();
    NoPrefixTable(const NoPrefixTable& src) = delete;
    NoPrefixTable& operator==(NoPrefixTable& src) = delete;
    NoPrefixTable(NoPrefixTable&& src) = delete;
    NoPrefixTable& operator==(NoPrefixTable&& src) = delete;

  private:
    //-------------------------------------------------------------
    // Private Initialisation routine
    //-------------------------------------------------------------

    void SetEntries() noexcept;

  public:
    //-------------------------------------------------------------
    // Operator Overloads
    //-------------------------------------------------------------

    // provide look up semantics
    [[nodiscard]] constexpr const enums& operator[](std::size_t index) const; 

  private:
    std::array<enums, TABLE_SIZE> m_buffer;
};

} // namespace trpp::instructions

#endif
