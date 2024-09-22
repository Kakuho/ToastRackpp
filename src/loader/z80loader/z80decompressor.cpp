#include "z80decompressor.hpp"

namespace Trpp::Loader{
using PageIndexType = std::uint8_t;
using DecompressedPage = std::vector<std::uint8_t>;
using PayloadType = std::pair<PageIndexType, DecompressedPage>;
using DecompressedLutType = std::unordered_map<PageIndexType, DecompressedPage>;

//-------------------------------------------------------------
//  Lifetime
//-------------------------------------------------------------

Z80Decompressor::Z80Decompressor()
  :
    m_index{0}
{

}

//-------------------------------------------------------------
//  Decompression 
//-------------------------------------------------------------

Z80ChunkHeader 
Z80Decompressor::GetChunkHeader(std::vector<std::uint8_t>& src){
  std::uint16_t length = src[0];
  length <<= 8;
  length |= src[1];
  return {
    .length = length,
    .page = src[2]
  };
}

Z80ChunkHeader 
Z80Decompressor::GetChunkHeader(std::uint8_t* src){
  std::uint16_t length = src[0];
  length <<= 8;
  length |= src[1];
  return {
    .length = length,
    .page = src[2]
  };
}


std::pair<PayloadType, std::size_t>
Z80Decompressor::DecompressChunk(std::vector<std::uint8_t>&& chunk){
  // Procedure to decompress 1 single chunk
  // Mayhaps more optimised than v1 since potentially less reallocations, however 
  // both still need to be tested for correctness and profiled for speed
  Z80ChunkHeader header = GetChunkHeader(chunk);
  // decompressed will be our output buffer
  DecompressedPage decompressed{};
  decompressed.reserve(header.length);
  // main decompression loop
  std::size_t index = 0x03;
  std::size_t startIndex = index;
  bool flag = false;
  while((index - 0x03) < header.length){
    if(chunk[index] != 0xED){
      index++;
      flag = true;
    }
    else{
      if(flag){
        // now we perform insertion
        decompressed.insert(decompressed.end(), 
            chunk.begin() + startIndex, chunk.begin() + index);
        flag = false;
      }
      if(chunk[index+1] == 0xED){
        std::uint8_t repetition = chunk[index+2];
        std::uint8_t byte = chunk[index+3];
        decompressed.insert(decompressed.end(), repetition, byte);
        index += 4;
      }
      else{
        decompressed.insert(decompressed.end(), {0xED, chunk[index+1]});
        index += 2;
      }
      // update the start to the new index
      startIndex = index;
    }
  } 
  // final check
  if(flag){
    decompressed.insert(decompressed.end(), 
        chunk.begin() + startIndex, chunk.begin() + index);
  }
  return {{header.page, decompressed}, index};
}

std::pair<PayloadType, std::size_t>
Z80Decompressor::DecompressChunk(std::uint8_t* chunk){
  // Procedure to decompress 1 single chunk
  // Mayhaps more optimised than v1 since potentially less reallocations, however 
  // both still need to be tested for correctness and profiled for speed
  Z80ChunkHeader header = GetChunkHeader(chunk);
  // decompressed will be our output buffer
  DecompressedPage decompressed{};
  decompressed.reserve(header.length);
  // main decompression loop
  std::size_t index = 0x03;
  std::size_t startIndex = index;
  bool flag = false;
  while((index - 0x03) < header.length){
    if(chunk[index] != 0xED){
      index++;
      flag = true;
    }
    else{
      if(flag){
        // now we perform insertion
        decompressed.insert(decompressed.end(), 
            chunk + startIndex, chunk + index);
        flag = false;
      }
      if(chunk[index+1] == 0xED){
        std::uint8_t repetition = chunk[index+2];
        std::uint8_t byte = chunk[index+3];
        decompressed.insert(decompressed.end(), repetition, byte);
        index += 4;
      }
      else{
        decompressed.insert(decompressed.end(), {0xED, chunk[index+1]});
        index += 2;
      }
      // update the start to the new index
      startIndex = index;
    }
  } 
  // final check
  if(flag){
    decompressed.insert(decompressed.end(), 
        chunk + startIndex, chunk + index);
  }
  return {{header.page, decompressed}, index};
}

DecompressedLutType 
Z80Decompressor::Decompress(std::vector<std::uint8_t>&& src){
  // src represents something we're reading only from, and should not alter
  std::size_t index = 0;
  DecompressedLutType lut{};
  while(index < src.size()){
    auto [decompressed, advance] = DecompressChunk(src.data() + index);
    auto [pageIndex, bytes] = decompressed;
    index += advance;
    lut[pageIndex] = bytes;
  }
  return lut;
}

} // namespace Trpp::Loader
