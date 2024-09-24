#include "decompression.hpp"

namespace Trpp::Loader::Z80{

using PageIndexType = std::uint8_t;
using DecompressedPage = std::vector<std::uint8_t>;
using DecompressedLut = 
  std::unordered_map<PageIndexType, DecompressedPage>;

// Version 1 .z80 decompression

DecompressedPage DecompressV1(const std::uint8_t* src){
  // Procedure to decompress a version 1 .z80 file.
  // decompressed will be our output buffer
  DecompressedPage decompressed{};
  decompressed.reserve(100);
  // main decompression loop
  std::size_t index = 0x00;
  std::size_t startIndex = index;
  bool flag = false;
  while(true){
    if(src[index] == 00){
      bool endcondition = 
        (src[index+1] == 0xED) &&
        (src[index+2] == 0xED) &&
        (src[index+3] == 0x00);
      if(endcondition) break;
    }
    else if(src[index] != 0xED){
      index++;
      flag = true;
    }
    else{
      if(flag){
        // now we perform insertion
        decompressed.insert(decompressed.end(), 
            src + startIndex, src + index);
        flag = false;
      }
      if(src[index+1] == 0xED){
        std::uint8_t repetition = src[index+2];
        std::uint8_t byte = src[index+3];
        decompressed.insert(decompressed.end(), repetition, byte);
        index += 4;
      }
      else{
        decompressed.insert(decompressed.end(), {0xED, src[index+1]});
        index += 2;
      }
      // update the start to the new index
      startIndex = index;
    }
  } 
  // final check
  if(flag){
    decompressed.insert(decompressed.end(), 
        src + startIndex, src + index);
  }
  return decompressed;
}

DecompressedPage DecompressV1(std::vector<std::uint8_t>& src){
  return DecompressV1(src.data());
}

// Version 2 .z80 Decompression

ChunkHeader GetChunkHeaderV23(std::uint8_t* src){
  std::uint16_t length = src[1];
  length <<= 8;
  length |= src[0];
  return {
    .length = length,
    .page = src[2]
  };
}

std::pair<PayloadEntry, std::size_t>
DecompressChunkV23(std::uint8_t* src){
  // Procedure to decompress 1 single chunk following the chunk layout 
  // in version 2 and 3
  ChunkHeader header = GetChunkHeaderV23(src);
  // decompressed will be our output buffer
  DecompressedPage decompressed{};
  decompressed.reserve(header.length);
  // main decompression loop
  std::size_t index = 0x03;
  std::size_t startIndex = index;
  bool flag = false;
  while((index - 0x03) < header.length){
    if(src[index] != 0xED){
      index++;
      flag = true;
    }
    else{
      if(flag){
        // now we perform insertion
        decompressed.insert(decompressed.end(), 
            src + startIndex, src + index);
        flag = false;
      }
      if(src[index+1] == 0xED){
        std::uint8_t repetition = src[index+2];
        std::uint8_t byte = src[index+3];
        decompressed.insert(decompressed.end(), repetition, byte);
        index += 4;
      }
      else{
        decompressed.insert(decompressed.end(), {0xED, src[index+1]});
        index += 2;
      }
      // update the start to the new index
      startIndex = index;
    }
  } 
  // final check
  if(flag){
    decompressed.insert(decompressed.end(), 
        src + startIndex, src + index);
  }
  return {  
    PayloadEntry{header.page, decompressed}, 
    index
  };
}

DecompressedLut DecompressV23(std::vector<std::uint8_t>& src){
  // src represents something we're reading only from, 
  // and should not alter
  std::size_t index = 0;
  DecompressedLut lut{};
  while(index < src.size()){
    auto [decompressed, advance] = 
      DecompressChunkV23(src.data() + index);
    auto [pageIndex, bytes] = decompressed;
    index += advance;
    lut[pageIndex] = bytes;
  }
  return lut;
}

DecompressedLut DecompressV23(std::uint8_t* src, std::size_t nbytes){
  // src represents something we're reading only from, 
  // and should not alter
  std::size_t index = 0;
  DecompressedLut lut{};
  while(index < nbytes){
    auto [decompressed, advance] = 
      DecompressChunkV23(src + index);
    auto [pageIndex, bytes] = decompressed;
    index += advance;
    lut[pageIndex] = bytes;
  }
  return lut;
}

} // namespace Trpp::Loader::Z80
