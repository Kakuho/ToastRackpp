#include "noprefix_table.hpp"

namespace trpp::instructions{

//-------------------------------------------------------------
// lifetime
//-------------------------------------------------------------

NoPrefixTable::NoPrefixTable(): m_buffer{}{
  m_buffer.fill(enums::Undefined);
  SetEntries();
}

void NoPrefixTable::SetEntries() noexcept{
  using enum enums;
  m_buffer[0x00] = NOP;
  m_buffer[0x01] = LD_dd_nn;
  m_buffer[0x02] = LD_bc_a;
}

//-------------------------------------------------------------
// Operator Overloads
//-------------------------------------------------------------

[[nodiscard]] constexpr const enums& 
NoPrefixTable::operator[](std::size_t index) const{
  assert(index < TABLE_SIZE);
  return m_buffer[index];
}

}
