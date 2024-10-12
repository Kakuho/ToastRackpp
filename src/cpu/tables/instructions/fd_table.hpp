#ifndef I_TABLE_FDPREFIX_HPP
#define I_TABLE_FDPREFIX_HPP

#include <array>
#include <cstdint>
#include <cassert>

#include "./../enums/fd_enums.hpp"

namespace Trpp::CPU::Instructions{

class FDTable{
  public:
    //-------------------------------------------------------------
    //  Constants
    //-------------------------------------------------------------
    
    static constexpr inline std::size_t TABLE_SIZE = 0xff;

    //-------------------------------------------------------------
    // lifetime
    //-------------------------------------------------------------

    FDTable();
    ~FDTable() = default;

    //  only allow default initialisation
    FDTable(const FDTable& src) = delete;
    FDTable& operator==(const FDTable& src) = delete;
    FDTable(FDTable&& src) = delete;
    FDTable& operator==(FDTable&& src) = delete;

    //-------------------------------------------------------------
    // Operator overloads
    //-------------------------------------------------------------
  
    //  provide read-only lookup semantics
    [[nodiscard]] FDenums operator[](std::size_t index) const;

  private:
    //-------------------------------------------------------------
    //  Used as a private initialisation routine
    //-------------------------------------------------------------
    
    void SetEntries() noexcept;

  private:
    std::array<FDenums, 0xFF> m_buffer;
};

} 

#endif
