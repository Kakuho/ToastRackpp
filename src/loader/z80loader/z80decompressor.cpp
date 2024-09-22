#include "z80decompressor.hpp"

namespace Trpp::Loader{
using PageIndexType = std::uint8_t;
using DecompressedPage = std::vector<std::uint8_t>;
using DecompressedLutType = std::unordered_map<PageIndexType, DecompressedPage>;

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

DecompressedPage 
Z80Decompressor::DecompressChunkV1(std::vector<std::uint8_t>&& chunk){
  // procedure to decompress 1 single chunk
  Z80ChunkHeader header = GetChunkHeader(chunk);
  // decompressed will be our output buffer
  DecompressedPage decompressed{};
  decompressed.reserve(header.length);
  // main decompression loop
  for(std::size_t i = 3; i < header.length; i++){
    if(chunk[i] == 0xED && chunk[i+1] == 0xED){
      std::uint8_t amount = chunk[i+2];
      std::uint8_t byte = chunk[i+3];
      decompressed.insert(decompressed.end(), amount, byte);
      i += 3;
    }
    else if(chunk[i] == 0xED && chunk[i+1] != 0xED){

      decompressed.insert(decompressed.end(), {0xED, chunk[i+1]});
      i += 2;
    }
    else{
      // I dont like this because it may perform a lot of reallocations...
      decompressed.push_back(chunk[i]);
    }
  }
  return decompressed;
}

DecompressedPage 
Z80Decompressor::DecompressChunkV2(std::vector<std::uint8_t>&& chunk){
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
  return decompressed;
}

DecompressedPage 
Z80Decompressor::DecompressChunkV2(std::uint8_t* chunk){
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
  return decompressed;
}

} // namespace Trpp::Loader
