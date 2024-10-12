#ifndef I_TABLE_EDPREFIX_HPP
#define I_TABLE_EDPREFIX_HPP

#include <array>
#include <cstdint>
#include <cassert>

#include "./../enums/ed_enums.hpp"

namespace Trpp::CPU::Instructions{

class EDTable{
  public:
    //-------------------------------------------------------------
    //  Constants
    //-------------------------------------------------------------
    
    static constexpr inline std::size_t TABLE_SIZE = 0xff;

    //-------------------------------------------------------------
    // lifetime
    //-------------------------------------------------------------

    EDTable();
    ~EDTable() = default;

    //  only allow default initialisation
    EDTable(const EDTable& src) = delete;
    EDTable& operator==(const EDTable& src) = delete;
    EDTable(EDTable&& src) = delete;
    EDTable& operator==(EDTable&& src) = delete;

    //-------------------------------------------------------------
    // Operator overloads
    //-------------------------------------------------------------
  
    //  provide read-only lookup semantics
    [[nodiscard]] EDenums operator[](std::size_t index) const;

  private:
    //-------------------------------------------------------------
    //  Used as a private initialisation routine
    //-------------------------------------------------------------
    
    void SetEntries() noexcept;

  private:
    std::array<EDenums, 0xFF> m_buffer;
};

} 

#endif
