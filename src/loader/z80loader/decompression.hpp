#ifndef LOADER_Z80LOADER_DECOMPRESSION
#define LOADER_Z80LOADER_DECOMPRESSION

#include <unordered_map>
#include <vector>
#include <iostream>
#include <utility>
#include <cstdint>

namespace Trpp::Loader::Z80{
  using PageIndexType = std::uint8_t;
  using DecompressedPage = std::vector<std::uint8_t>;
  using DecompressedLut = 
    std::unordered_map<PageIndexType, DecompressedPage>;

  struct ChunkHeader{
    std::uint16_t length;
    std::uint8_t page;
  };

  struct PayloadEntry{
    PageIndexType index;
    DecompressedPage bytes;
  };

  // Version 1 .z80 decompression

  DecompressedPage DecompressV1(const std::uint8_t* src);
  DecompressedPage DecompressV1(std::vector<std::uint8_t>& src);

  // Version 2 .z80 Decompression

  ChunkHeader GetChunkHeaderV23(std::uint8_t* src);

  std::pair<PayloadEntry, std::size_t> 
  DecompressChunkV23(std::uint8_t* src);

  DecompressedLut DecompressV23(std::vector<std::uint8_t>& src);

  DecompressedLut DecompressV23(std::uint8_t* src, std::size_t nbytes);
}

#endif
