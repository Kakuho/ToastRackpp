#ifndef LOADER_Z80LOADER_DECOMPRESSOR
#define LOADER_Z80LOADER_DECOMPRESSOR

// .z80 comes in four varieties:
//
//  * Version 1 + No Compression => NOP
//
//  * Version 1 + Compression (Byte[12].5 == 1) => Standard decompression
//         
//      The compression method is very simple: it replaces repetitions of 
//      at least five equal bytes by a four-byte code ED ED xx yy, which 
//      stands for "byte yy repeated xx times". Only sequences of length 
//      at least 5 are coded. 
//
//      The exception is sequences consisting of ED's; if they are 
//      encountered, even two ED's are encoded into ED ED 02 ED. 
//
//      Finally, every byte directly following a single ED is not taken 
//      into a block, for example ED 6*00 is not encoded 
//      into ED ED ED 06 00 but into ED 00 ED ED 05 00. 
//
//      The block is terminated by an end marker, 00 ED ED 00.
//      [https://worldofspectrum.org/faq/reference/z80format.htm]
//
//  * Version 2 and Version 3 follows the same compression scheme, 
//    however the structure of a compressed block is slightly different:
//        
//      i) They consist of a header:
//
//      Byte    Length  Description 
//      ---------------------------
//      0       2       Length of compressed data (without this 3-byte 
//                      header)
//                      If length=0xffff, data is 16384 bytes long and 
//                      not compressed
//      2       1       Page number of block
//      3       [0]     Data
//
//      ii) They do not have an end marker

#include <unordered_map>
#include <vector>
#include <iostream>
#include <utility>
#include <cstdint>


namespace Trpp::Loader{

  struct Z80ChunkHeader{
    std::uint16_t length;
    std::uint8_t page;
  };

  class Z80Decompressor{
    using PageIndexType = std::uint8_t;
    using DecompressedPage = std::vector<std::uint8_t>;
    using PayloadType = std::pair<PageIndexType, DecompressedPage>;
    using DecompressedLutType = 
      std::unordered_map<PageIndexType, DecompressedPage>;

    public:
      //-------------------------------------------------------------
      //  Lifetime
      //-------------------------------------------------------------

      Z80Decompressor();

      //-------------------------------------------------------------
      //  Decompression For Version 1 .Z80 files
      //-------------------------------------------------------------

      DecompressedPage DecompressV1(std::vector<std::uint8_t>&& src);
      DecompressedPage DecompressV1(std::uint8_t* src);

      //-------------------------------------------------------------
      //  Decompression For Version 2 / 3 .Z80 files
      //-------------------------------------------------------------

      Z80ChunkHeader GetChunkHeaderV23(std::vector<std::uint8_t>& src);
      Z80ChunkHeader GetChunkHeaderV23(std::uint8_t* src);

      std::pair<PayloadType, std::size_t> 
      DecompressChunkV23(std::vector<std::uint8_t>&& src);

      std::pair<PayloadType, std::size_t>
      DecompressChunkV23(std::uint8_t* src);

      DecompressedLutType DecompressV23(std::vector<std::uint8_t>&& src);

    private:
      DecompressedLutType data;
      std::size_t m_index;
  };
}

#endif
