#include "baseLoader.hpp"
#include <fstream>

namespace Trpp::Loader{

// ------------------------------------------------------ //
// Lifetime
// ------------------------------------------------------ //

BaseLoader::BaseLoader(std::string& filename)
    : 
      m_index{0},
      m_filename{filename}
{
  LoadFile();
}

void BaseLoader::LoadFile(){
  std::ifstream inputfile{
    m_filename, std::ios::in | std::ios::ate | std::ios::binary

  };
  if(!inputfile){
    throw std::runtime_error{"Input file error"};
  }
  std::size_t filesize = inputfile.tellg();
  std::cout << "filesize :: " << filesize << '\n';
  // now we place all the bytes into ram
  bytes.reserve(filesize);
  bytes.resize(filesize);
  inputfile.seekg(0);
  if(!inputfile.read(&bytes[0], filesize)){
    throw std::runtime_error{"error reading bytes into vector buffer"};
  }
}

//-------------------------------------------------------------
//  Printing Functions
//-------------------------------------------------------------

void BaseLoader::PrintRawBytes(std::size_t beg, std::size_t end) const{
  // dirty hack to make sure beg starts from 1, even if you put 0.
  beg++;    
  bool midbreak = false;
  std::cout << std::setw(8) << std::setfill('0') << beg-1 
            << std::setw(3) << std::setfill(' ') << ' ';
  for(std::size_t i = beg; i < end + 1; i++){
    std::cout << std::hex << std::setw(2) << std::setfill('0') 
              << std::bitset<8>(bytes[i - 1]).to_ulong();
    if((i % 16 == 0) && (i != 0)){
      std::cout << '\n';
      std::cout << std::setw(8) << std::setfill('0') 
                << i << std::setw(3) << std::setfill(' ') << ' ';
      midbreak = false;
    }
    else if((i % 8 == 0 ) && (i != 0) && !midbreak){
      midbreak = true;
      std::cout << std::setw(4) << std::setfill(' ') << ' ' ;
    }
    else{
      std::cout << ' ';
    }
  }
  std::cout << '\n';
}

} // namespace Trpp::Loader
