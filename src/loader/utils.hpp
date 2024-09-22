#ifndef LOADER_HPP
#define LOADER_HPP

// shared utilities for file loading

#include <cstdint>
#include <string>
#include <stdexcept>

namespace Trpp::Loader{

enum class Extension: std::uint8_t{
  Unknown, Z80, Tap
};

inline Extension ParseExtension(std::string& filename){
  using enum Extension;
  bool hasdot = false;
  std::string substr;
  for(std::size_t i = 0; i < filename.size(); i++){
    if(filename[i] == '.'){
      substr = filename.substr(i+1, filename.size());
      hasdot = true;
      break;
    }
  }
  if(hasdot == false){
    throw std::runtime_error{"Error::Cannot_find_file_extension"};
  }
  if(substr == "z80"){
    return Extension::Z80;
  }
  if(substr == "tap"){
    return Extension::Tap;
  }
  else{
    return Extension::Unknown;
  }
}

} // namespace Trpp::Loader

#endif
