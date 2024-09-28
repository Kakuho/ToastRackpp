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
#include <cstdint>

namespace Trpp::Loader{

class BaseLoader{
  public:
    //-------------------------------------------------------------
    //  Lifetime
    //-------------------------------------------------------------

    explicit BaseLoader(std::string& filename);
    explicit BaseLoader(std::string&& filename);

    std::size_t FileSize() const{ return bytes.size();}

  private:
    void LoadFile();

  public:
    //-------------------------------------------------------------
    //  Printing Functions
    //-------------------------------------------------------------

    void PrintRawBytes(std::size_t beg, std::size_t end) const;

    void PrintRawBytes(std::size_t n) const
    { PrintRawBytes(0, n); }

    void PrintRawBytes() const
    { PrintRawBytes(0, bytes.size()-1); }

  protected:

    void virtual CheckFileName() const = 0;

    // ------------------------------------------------------ //
    // Cursor Operations
    // ------------------------------------------------------ //

    std::size_t GetIndex() const noexcept{ return m_index;}
    void SetIndex(std::size_t val) noexcept{ m_index = val; }

    // ------------------------------------------------------ //
    // Memory Fetching
    // ------------------------------------------------------ //

    std::uint8_t ReadByte(std::size_t index) const { return bytes[index];}

    std::uint16_t ReadWord(std::size_t index) const { 
      return (
          static_cast<std::uint16_t>(
            static_cast<std::uint8_t>(bytes[index+1])) << 8) | 
            static_cast<std::uint8_t>(bytes[index]
          );
    }

    // Data Representation

    std::vector<char> bytes;
    std::size_t m_index;
    std::string& m_filename;
};

} // namespace Trpp::Loader

#endif
