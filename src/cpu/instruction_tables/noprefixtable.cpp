#include "noprefix_table.hpp"

namespace trpp::instructions{

  NoPrefixTable::NoPrefixTable(): m_buffer{}{
    m_buffer.fill(noprefix_enums::Undefined);
    SetEntries();
  }

  void NoPrefixTable::SetEntries() noexcept{
    using enum noprefix_enums;
    m_buffer[0x00] = NOP;
    m_buffer[0x01] = LD_dd_nn;
    m_buffer[0x02] = LD_bc_a;
  }

}
