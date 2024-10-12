#ifndef I_TABLE_FDCBPREFIX_HPP
#define I_TABLE_FDCBPREFIX_HPP

#include <array>
#include <cstdint>
#include <cassert>

#include "./../enums/fdcb_enums.hpp"

namespace Trpp::CPU::Instructions{

class FDCBTable{
  public:
    //-------------------------------------------------------------
    //  Constants
    //-------------------------------------------------------------
    
    static constexpr inline std::size_t TABLE_SIZE = 0xff;

    //-------------------------------------------------------------
    // lifetime
    //-------------------------------------------------------------

    FDCBTable();
    ~FDCBTable() = default;

    //  only allow default initialisation
    FDCBTable(const FDCBTable& src) = delete;
    FDCBTable& operator==(const FDCBTable& src) = delete;
    FDCBTable(FDCBTable&& src) = delete;
    FDCBTable& operator==(FDCBTable&& src) = delete;

    //-------------------------------------------------------------
    // Operator overloads
    //-------------------------------------------------------------
  
    //  provide read-only lookup semantics
    [[nodiscard]] FDCBenums operator[](std::size_t index) const;

  private:
    //-------------------------------------------------------------
    //  Used as a private initialisation routine
    //-------------------------------------------------------------
    
    void SetEntries() noexcept;

  private:
    std::array<FDCBenums, 0xFF> m_buffer;
};

} 

#endif
