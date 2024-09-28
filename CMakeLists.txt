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
      src/cpu/tables/instructions/cb_table.cpp

      # 48k
      src/48k/zxmemory48k.cpp
      src/48k/spectrum48k.cpp

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

add_executable(toastrack src/main.cpp ${CXX_SRCS})

target_compile_options(toastrack PRIVATE -g -std=c++20)

#set_target_properties(toastrack PROPERTIES CXX_EXTENSIONS OFF)

#add_custom_command(
#    TARGET toastrack
#    POST_BUILD
#    COMMAND toastrack
#)

# unit tests

find_package(Catch2 3 REQUIRED)

set(TEST_SRCS 
        # cpu tests
        tests/cpu/general.cpp
        tests/cpu/registerdecoding.cpp
        # 8 bit tests
        tests/cpu/8bitload/ld_r_r.cpp 
        tests/cpu/8bitload/ld_r_n.cpp
        tests/cpu/8bitload/ld_r_hl.cpp
        tests/cpu/8bitload/ld_r_idx.cpp
        tests/cpu/8bitload/ld_hl_r.cpp
        tests/cpu/8bitload/ld_hl_n.cpp
        # bridge
        tests/cpu/bridge/bridge.cpp

        # memory tests
        tests/memory/48kmemory.cpp

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

add_executable(tests ${TEST_SRCS} ${CXX_SRCS})

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

target_compile_options(tests PRIVATE -g -std=c++20)

########

add_subdirectory(src)

add_subdirectory(tests)
