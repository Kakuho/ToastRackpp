#ifndef I_TABLE_CBPREFIX_HPP
#define I_TABLE_CBPREFIX_HPP

#include <array>
#include <cstdint>

#include "enums/cbenums.hpp"

namespace trpp::instructions{

  class CBTable{
    public:
      // lifetime
      CBTable();
      //  only allow default initialisation
      CBTable(const CBTable& src) = delete;
      CBTable& operator==(const CBTable& src) = delete;
      CBTable(CBTable&& src) = delete;
      CBTable& operator==(CBTable&& src) = delete;

    public:
      // operational
      void SetEntries() noexcept;

    public:
      // operator overloads
      //  provide read-only lookup semantics
      [[nodiscard]] const CBenums& 
        operator[](std::size_t index) const noexcept; 

    private:
      // internal buffer
      std::array<CBenums, 0xFF> m_buffer;
  };


} // namespace trpp::instructions

#endif
