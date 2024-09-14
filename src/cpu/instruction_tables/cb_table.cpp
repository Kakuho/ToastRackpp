#include "cb_table.hpp"

namespace trpp::instructions{

//-------------------------------------------------------------
// lifetime
//-------------------------------------------------------------

CBTable::CBTable(): m_buffer{}{
  m_buffer.fill(CBenums::undefined);
  SetEntries();
}

//-------------------------------------------------------------
// Operational
//-------------------------------------------------------------

void CBTable::SetEntries() noexcept{
  using enum CBenums;
}

//-------------------------------------------------------------
// Operator overloads
//-------------------------------------------------------------

[[nodiscard]] constexpr const CBenums& 
CBTable::operator[](std::size_t index) const noexcept{ 
  assert(index < TABLE_SIZE);
  return m_buffer[index];
}

} // namespace trpp::instructions
