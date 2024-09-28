#ifndef SNALOADER_SNALOADER_HPP
#define SNALOADER_SNALOADER_HPP

// Class for loading .sna memory snapshots files into system memory.
//
// Reference: https://worldofspectrum.org/faq/reference/formats.htm

#include <stdexcept>
#include <string>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <bitset>
#include <cassert>
#include <vector>
#include <stdexcept>

#include "loader/baseLoader.hpp"
#include "loader/utils.hpp"
#include "48k/zxmemory48k.hpp"

namespace Trpp::Loader{

class SnaLoader : public BaseLoader{
  struct Unimplemented{};

  public:
    //-------------------------------------------------------------
    // Lifetime
    //-------------------------------------------------------------

    explicit SnaLoader(std::string& filename);
    SnaLoader() = delete;
    SnaLoader(const SnaLoader& src) = delete;
    ~SnaLoader() = default;

  private:
      void virtual CheckFileName() const override;

  public:
    //-------------------------------------------------------------
    //  System Integration Functions
    //-------------------------------------------------------------

    void Load(ZxMemory48K& memory) const;

  private:
    void Dump48k(ZxMemory48K& memory) const;

  public:
    //-------------------------------------------------------------
    //  Parsing Header Information
    //-------------------------------------------------------------

    //-------------------------------------------------------------
    //  Detection code
    //-------------------------------------------------------------

    // .sna files are split up for either 48k or 128k
    // 48ks are 49179 bytes long
    // 128ks are 131103 or 1474787 bytes long
    
    bool Is48k()  const{ return FileSize() == 49179; }
    bool Is128k() const{ return (FileSize() == 131103) || (FileSize() == 147487); }

    //-------------------------------------------------------------
    // Printing Functions
    //-------------------------------------------------------------

    void PrintSpectrumModel() const;
    void PrintHeader() const;

  private:
};

} // namespace Trpp::Loader

#endif
