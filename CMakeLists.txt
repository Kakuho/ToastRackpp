cmake_minimum_required(VERSION 3.1...3.29)

project(ToastRackpp VERSION 1.0 
                    LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# main 

include_directories(src)

set(CXX_SRCS 
      # Z80 Cpu
      src/cpu/z80.cpp 
      src/cpu/z80bridge.cpp 
      src/cpu/z80registers.cpp 
      src/cpu/debugz80.cpp
      # Instruction Tables
      src/cpu/tables/instructions/noprefix_table.cpp
      src/cpu/tables/instructions/ed_table.cpp
      src/cpu/tables/instructions/cb_table.cpp
      src/cpu/tables/instructions/dd_table.cpp
      src/cpu/tables/instructions/ddcb_table.cpp
      src/cpu/tables/instructions/fd_table.cpp
      src/cpu/tables/instructions/fdcb_table.cpp

      # 48k
      src/48k/zxmemory48k.cpp
      src/48k/spectrum48k.cpp
      src/48k/vram_utils.cpp

      # File loaders
      src/loader/baseLoader.cpp 
      # Z80
      src/loader/z80loader/z80loader.cpp 
      src/loader/z80loader/z80decompressor.cpp
      src/loader/z80loader/decompression.cpp
      # TAP
      src/loader/taploader/taploader.cpp
      # SNA
      src/loader/snaloader/snaloader.cpp
)

# construct the toastrack static library
add_library(toastrack SHARED ${CXX_SRCS})
target_compile_options(toastrack PRIVATE -g -std=c++20)

# construct main program with toastrack as a dependency
add_executable(main src/main.cpp)
target_link_libraries(main toastrack)
target_compile_options(main PRIVATE -std=c++20)

#############################

# unit tests

# the strange structure is so that I can selectively rebuild some tests which im currently targeting

find_package(Catch2 3 REQUIRED)

set(CPU_TEST_SRCS
        # cpu tests
        tests/cpu/general.cpp
        tests/cpu/registerdecoding.cpp
        # bridge
        tests/cpu/bridge/bridge.cpp

        # 8 bit tests
        tests/cpu/8bitload/ld_r_r.cpp 
        tests/cpu/8bitload/ld_r_n.cpp
        tests/cpu/8bitload/ld_r_hl.cpp
        tests/cpu/8bitload/ld_r_idx.cpp
        tests/cpu/8bitload/ld_hl_r.cpp
        tests/cpu/8bitload/ld_hl_n.cpp
)


set(CURRENT_CPU_TEST_SRCS
        tests/cpu/8bitload/ld_r_r.cpp 
)

#####

set(SYSTEM_TEST_SRCS
        # memory tests
        tests/memory/48kmemory.cpp
        tests/memory/vram.cpp
)

set(CURRENT_SYSTEM_TEST_SRCS
        tests/memory/vram.cpp
)

#####

set(LOADER_TEST_SRCS
        # loader tests
        tests/loader/parses_extension.cpp

        # Z80 files
        tests/loader/tetrisloader.cpp
        tests/loader/z80loader/version2/chunking_version2_vector.cpp
        tests/loader/z80loader/version2/chunking_version2_pointer.cpp
        tests/loader/z80loader/version2/chunking_version2_big.cpp
        tests/loader/z80loader/version1/chunking_version1_vector.cpp
        tests/loader/z80loader/version1/chunking_version1_pointer.cpp
)

set(CURRENT_LOADER_TEST_SRCS
)

#####

set(TEST_SRCS 
      ${CURRENT_CPU_TEST_SRCS}
      ${CURRENT_SYSTEM_TEST_SRCS}
      ${CURRENT_LOADER_TEST_SRCS}
)

add_executable(tests ${TEST_SRCS})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain toastrack)
target_compile_options(tests PRIVATE -g -std=c++20)
