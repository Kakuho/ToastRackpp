#ifndef BASELOADER_HPP
#define BASELOADER_HPP

// base class file loader for spectrum file formats

#include <ostream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <bitset>

namespace trpp{

class BaseLoader{
  public:
    BaseLoader(std::string&& filename)
      : m_filename{std::move(filename)},
        m_index{0}{
      LoadFile();
    }

  void PrintRawBytes(std::size_t beg, std::size_t end) const{
    beg++;    // dirty hack to make sure beg starts from 1, even if you put 0.
    bool midbreak = false;
    std::cout << std::setw(8) << std::setfill('0') << beg-1 << std::setw(3) << std::setfill(' ') << ' ';
    for(std::size_t i = beg; i < end + 1; i++){
      std::cout << std::hex << std::setw(2) << std::setfill('0') << std::bitset<8>(bytes[i - 1]).to_ulong();
      if((i % 16 == 0) && (i != 0)){
        std::cout << '\n';
        std::cout << std::setw(8) << std::setfill('0') << i << std::setw(3) << std::setfill(' ') << ' ';
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

  void PrintRawBytes(std::size_t n) const{
    PrintRawBytes(0, n);
  }

  void PrintRawBytes() const{
    PrintRawBytes(0, bytes.size()-1);
  }

  protected:
    void virtual CheckFileName() const = 0;
    std::size_t GetIndex() const{ return m_index;}
    std::size_t SetIndex(std::size_t val) const{ return m_index; }
    std::uint8_t ReadByte(std::size_t index) const { return bytes[index];}
    std::uint16_t ReadWord(std::size_t index) const { 
      return (static_cast<std::uint16_t>(static_cast<std::uint8_t>(bytes[index+1])) << 8) | 
        static_cast<std::uint8_t>(bytes[index]);
    }
    std::vector<char> bytes;
    std::size_t m_index;
    std::string m_filename;

  private:
    // implementation detail, loader is RAII object for raw bytes
    void LoadFile(){
      std::ifstream inputfile{m_filename, std::ios::in | std::ios::ate | std::ios::binary};
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
};

} // namespace trpp

#endif
