#ifndef I_TABLE_DDPREFIX_HPP
#define I_TABLE_DDPREFIX_HPP

#include <array>
#include <cstdint>
#include <cassert>

#include "./../enums/dd_enums.hpp"

namespace Trpp::CPU::Instructions{

class DDTable{
  public:
    //-------------------------------------------------------------
    //  Constants
    //-------------------------------------------------------------
    
    static constexpr inline std::size_t TABLE_SIZE = 0xff;

    //-------------------------------------------------------------
    // lifetime
    //-------------------------------------------------------------

    DDTable();
    ~DDTable() = default;

    //  only allow default initialisation
    DDTable(const DDTable& src) = delete;
    DDTable& operator==(const DDTable& src) = delete;
    DDTable(DDTable&& src) = delete;
    DDTable& operator==(DDTable&& src) = delete;

    //-------------------------------------------------------------
    // Operator overloads
    //-------------------------------------------------------------
  
    //  provide read-only lookup semantics
    [[nodiscard]] DDenums operator[](std::size_t index) const;

  private:
    //-------------------------------------------------------------
    //  Used as a private initialisation routine
    //-------------------------------------------------------------
    
    void SetEntries() noexcept;

  private:
    std::array<DDenums, 0xFF> m_buffer;
};

} 

#endif
