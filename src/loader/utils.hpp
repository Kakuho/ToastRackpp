#ifndef LOADER_HPP
#define LOADER_HPP

// shared utilities for file loading

#include <cstdint>
#include <string>

namespace trpp::loader{

enum class Extension: std::uint8_t{
  Z80, Tap
};

inline Extension ParseExtension(std::string& filename){

}

} // namespace trpp::loader

#endif
