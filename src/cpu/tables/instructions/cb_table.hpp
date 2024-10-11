#ifndef I_TABLE_CBPREFIX_HPP
#define I_TABLE_CBPREFIX_HPP

#include <array>
#include <cstdint>
#include <cassert>

#include "./../enums/cb_enums.hpp"

namespace Trpp::CPU::Instructions{

class CBTable{
  public:
    //-------------------------------------------------------------
    //  Constants
    //-------------------------------------------------------------
    
    static constexpr inline std::size_t TABLE_SIZE = 0xff;

    //-------------------------------------------------------------
    // lifetime
    //-------------------------------------------------------------

    CBTable();
    ~CBTable() = default;

    //  only allow default initialisation
    CBTable(const CBTable& src) = delete;
    CBTable& operator==(const CBTable& src) = delete;
    CBTable(CBTable&& src) = delete;
    CBTable& operator==(CBTable&& src) = delete;

    //-------------------------------------------------------------
    // Operator overloads
    //-------------------------------------------------------------
  
    //  provide read-only lookup semantics
    [[nodiscard]] CBenums operator[](std::size_t index) const;

  private:
    //-------------------------------------------------------------
    //  Used as a private initialisation routine
    //-------------------------------------------------------------
    
    void SetEntries() noexcept;

  private:
    std::array<CBenums, 0xFF> m_buffer;
};

} 

#endif
