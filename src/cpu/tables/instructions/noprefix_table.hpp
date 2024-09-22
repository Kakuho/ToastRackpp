#ifndef I_TABLE_NOPREFIX_HPP
#define I_TABLE_NOPREFIX_HPP

// NoPrefixTable is a LUT for instructions with no prefixes
//
// Reference:

#include <array>
#include <cstdint>
#include <cassert>

#include "./../enums/enums.hpp"

namespace Trpp::CPU::Instructions{

class NoPrefixTable{
  public:
    //-------------------------------------------------------------
    //  Constants
    //-------------------------------------------------------------

    static constexpr std::size_t TABLE_SIZE = 0xff;

    //-------------------------------------------------------------
    // lifetime
    //-------------------------------------------------------------

    // only provide construction semantics
    NoPrefixTable();
    // no copying or moving
    NoPrefixTable(const NoPrefixTable& src) = delete;
    NoPrefixTable& operator==(NoPrefixTable& src) = delete;
    NoPrefixTable(NoPrefixTable&& src) = delete;
    NoPrefixTable& operator==(NoPrefixTable&& src) = delete;

  private:
    //-------------------------------------------------------------
    // Private Initialisation routine
    //    populates the table with the required instructions
    //-------------------------------------------------------------

    void SetEntries() noexcept;

    void Set8BitLoadGroup() noexcept;
    void Set16BitLoadGroup() noexcept;
    void SetExchangeGroup() noexcept;
    void Set8bitAluGroup() noexcept;
    void SetGeneralGroup() noexcept;
    void Set16bitAluGroup() noexcept;
    void SetRotateShiftGroup() noexcept;
    void SetJumpGroup() noexcept;
    void SetCallReturnGroup() noexcept;

  public:
    //-------------------------------------------------------------
    // Operator Overloads
    //-------------------------------------------------------------

    // provide look up semantics
    [[nodiscard]] enums 
    operator[](std::size_t index) const;

  private:
    std::array<enums, TABLE_SIZE> m_buffer;
};

} 

#endif
