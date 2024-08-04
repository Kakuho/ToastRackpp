#ifndef I_TABLE_NOPREFIX_HPP
#define I_TABLE_NOPREFIX_HPP

#include <array>
#include <cstdint>

#include "enums/noenums.hpp"


namespace trpp::instructions{

  class NoPrefixTable{
    public:
      // lifetime
      NoPrefixTable();
      NoPrefixTable(NoPrefixTable&& src) = delete;
      NoPrefixTable& operator==(NoPrefixTable&& src) = delete;

    public:
      // operational
      void SetEntries() noexcept;

    public:
      // operator overloads
      //  provide readonly lookup semantics
      [[nodiscard]] const noprefix_enums& 
        operator[](std::size_t index) const noexcept; 

    private:
      // internal buffer
      std::array<noprefix_enums, 0xFF> m_buffer;
  };


} // namespace trpp::instructions

#endif
