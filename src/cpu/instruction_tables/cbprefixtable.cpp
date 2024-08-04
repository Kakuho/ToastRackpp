#include "CBprefix_table.hpp"

namespace trpp::instructions{

  CBTable::CBTable(): m_buffer{}{
    m_buffer.fill(CBenums::undefined);
  }

  void CBTable::SetEntries() noexcept{
    using enum CBenums;
  }

} // namespace trpp::instructions
