#ifndef I_TABLE_DDCBPREFIX_HPP
#define I_TABLE_DDCBPREFIX_HPP

#include <array>
#include <cstdint>
#include <cassert>

#include "./../enums/ddcb_enums.hpp"

namespace Trpp::CPU::Instructions{

class DDCBTable{
  public:
    //-------------------------------------------------------------
    //  Constants
    //-------------------------------------------------------------
    
    static constexpr inline std::size_t TABLE_SIZE = 0xff;

    //-------------------------------------------------------------
    // lifetime
    //-------------------------------------------------------------

    DDCBTable();
    ~DDCBTable() = default;

    //  only allow default initialisation
    DDCBTable(const DDCBTable& src) = delete;
    DDCBTable& operator==(const DDCBTable& src) = delete;
    DDCBTable(DDCBTable&& src) = delete;
    DDCBTable& operator==(DDCBTable&& src) = delete;

    //-------------------------------------------------------------
    // Operator overloads
    //-------------------------------------------------------------
  
    //  provide read-only lookup semantics
    [[nodiscard]] DDCBenums operator[](std::size_t index) const;

  private:
    //-------------------------------------------------------------
    //  Used as a private initialisation routine
    //-------------------------------------------------------------
    
    void SetEntries() noexcept;

  private:
    std::array<DDCBenums, 0xFF> m_buffer;
};

} 

#endif
