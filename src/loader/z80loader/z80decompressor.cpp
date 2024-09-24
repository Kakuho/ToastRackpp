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
//  Decompression For Version 1 .Z80 files
//-------------------------------------------------------------

DecompressedPage 
Z80Decompressor::DecompressV1(std::vector<std::uint8_t>&& src){
  // Procedure to decompress a version 1 .z80 file.
  // decompressed will be our output buffer
  DecompressedPage decompressed{};
  decompressed.reserve(src.size());
  // main decompression loop
  std::size_t index = 0x00;
  std::size_t startIndex = index;
  bool flag = false;
  while(true){
    if(src[index] == 0x00){
      bool endcondition = 
        (src[index+1] == 0xED) &&
        (src[index+2] == 0xED) &&
        (src[index+3] == 0x00);
      if(endcondition) break;
    }
    if(src[index] != 0xED){
      index++;
      flag = true;
    }
    else{
      if(flag){
        // now we perform insertion
        decompressed.insert(decompressed.end(), 
            src.begin() + startIndex, src.begin() + index);
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
        src.begin() + startIndex, src.begin() + index);
  }
  return decompressed;
}

DecompressedPage 
Z80Decompressor::DecompressV1(std::uint8_t* src){
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

//-------------------------------------------------------------
//  Decompression For Version 2 / 3 .Z80 files
//-------------------------------------------------------------

Z80ChunkHeader 
Z80Decompressor::GetChunkHeaderV23(std::vector<std::uint8_t>& src){
  std::uint16_t length = src[0];
  length <<= 8;
  length |= src[1];
  return {
    .length = length,
    .page = src[2]
  };
}

Z80ChunkHeader 
Z80Decompressor::GetChunkHeaderV23(std::uint8_t* src){
  std::uint16_t length = src[0];
  length <<= 8;
  length |= src[1];
  return {
    .length = length,
    .page = src[2]
  };
}

std::pair<PayloadType, std::size_t>
Z80Decompressor::DecompressChunkV23(std::vector<std::uint8_t>&& chunk){
  // Procedure to decompress 1 single chunk following the chunk
  // layout in version 2 and 3
  Z80ChunkHeader header = GetChunkHeaderV23(chunk);
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
Z80Decompressor::DecompressChunkV23(std::uint8_t* chunk){
  // Procedure to decompress 1 single chunk following the chunk layout 
  // in version 2 and 3
  Z80ChunkHeader header = GetChunkHeaderV23(chunk);
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
Z80Decompressor::DecompressV23(std::vector<std::uint8_t>&& src){
  // src represents something we're reading only from, 
  // and should not alter
  std::size_t index = 0;
  DecompressedLutType lut{};
  while(index < src.size()){
    auto [decompressed, advance] = 
      DecompressChunkV23(src.data() + index);
    auto [pageIndex, bytes] = decompressed;
    index += advance;
    lut[pageIndex] = bytes;
  }
  return lut;

}

} // namespace Trpp::Loader
