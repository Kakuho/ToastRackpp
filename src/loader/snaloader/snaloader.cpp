#include "snaloader.hpp"
#include "loader/utils.hpp"
#include "loader/z80loader/decompression.hpp"
#include <stdexcept>

namespace Trpp::Loader{

//-------------------------------------------------------------=
//  Lifetime
//-------------------------------------------------------------

SnaLoader::SnaLoader(std::string& filename)
  :
    BaseLoader(filename)
{
  //CheckFileName();
}

void SnaLoader::CheckFileName() const {
  Extension ext = ParseExtension(m_filename);
  //assert(ext == Extension::Z80);
}

//-------------------------------------------------------------
//  System Integration Functions
//-------------------------------------------------------------

void SnaLoader::Load(ZxMemory48K& memory) const{
  if(Is48k()){
    std::cout << ".SNA file Is 48k\n";
    Dump48k(memory);
  }
  else if(Is128k()){
    std::cout << ".SNA file Is 128k\n";
  }
  else{
      throw std::runtime_error{"Unrecognised .z80 version"};
  }
}

void SnaLoader::Dump48k(ZxMemory48K& memory) const{
  for(std::size_t i = 27; i < bytes.size(); i++){
    memory[0x4000 + i - 27] = ReadByte(i);
  }
}

} // namespace Trpp::Loader
