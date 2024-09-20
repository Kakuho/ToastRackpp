#include <concepts>
#include <type_traits>

#include "enums/noenums.hpp"
#include "enums/cbenums.hpp"

namespace trpp::instructions{

  template<typename T>
  concept TableEnumType = 
  std::same_as<T, noprefix_enums> || std::same_as<T, CBenums>;

}
