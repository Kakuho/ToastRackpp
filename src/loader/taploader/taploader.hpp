#ifndef TAPLOADER_HPP
#define TAPLOADER_HPP

// utilities for loading .tap files

#include <cstdint>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <iomanip>
#include <bitset>

#include "./../baseLoader.hpp"

namespace Trpp::Loader{

class TapLoader : public BaseLoader{
  public:
  TapLoader(std::string&& filename): BaseLoader(std::move(filename)){
  }

  void LoadChunk(){
    if(m_index == 0){
      m_currentChunk = reinterpret_cast<char*>(&bytes[m_index]);
      std::size_t length = m_currentChunk[0] + m_currentChunk[1];
      std::cout << "length of chunk: " << length << '\n';
      char* start = &m_currentChunk[2];
      char* end = start + length;
      for(char* pt = start; pt < end; pt++){
        std::cout << *pt;
      }
      std::cout << '\n';
      for(char* pt = start; pt < end; pt++){
        std::cout << std::bitset<8>(*pt).to_ulong() << ' ';
      }
    }
  }

  void PrintChunks(){
    while(m_index < bytes.size()){
      m_currentChunk = reinterpret_cast<char*>(&bytes[m_index]);
      std::size_t length = m_currentChunk[0] + m_currentChunk[1];
      length &= 0xFF;
      std::cout << std::hex << "length of chunk: " << length << '\n';
      char* start = &m_currentChunk[2];
      char* end = start + length;
      for(char* pt = start; pt < end; pt++){
        std::cout << *pt;
      }
      std::cout << '\n';
      for(char* pt = start; pt < end; pt++){
        std::cout << std::bitset<8>(*pt).to_ulong() << ' ';
      }
      std::cout << '\n';
      m_index += length + 2;
    }
  }

  private:
  char* m_currentChunk;
  void virtual CheckFileName() const override{

  }
};

} // namespace trpp

#endif
