cmake_minimum_required(VERSION 3.1...3.29)

project(ToastRackpp VERSION 1.0 
                    LANGUAGES CXX)

# main 

include_directories(src)

set(CXX_SRCS 
      # Z80 Cpu
      src/cpu/z80.cpp 
      src/cpu/z80registers.cpp 
      src/cpu/debugz80.cpp
      # Instruction Tables
      src/cpu/instruction_tables/cb_table.cpp
      src/cpu/instruction_tables/noprefix_table.cpp

      # File loaders
      src/loader/baseLoader.cpp 
      src/loader/z80loader/z80loader.cpp 
      src/loader/taploader/taploader.cpp
   )

add_executable(toastrack src/main.cpp ${CXX_SRCS})

target_compile_features(toastrack PUBLIC cxx_std_20)

set_target_properties(toastrack PROPERTIES CXX_EXTENSIONS OFF)

#add_custom_command(
#    TARGET toastrack
#    POST_BUILD
#    COMMAND toastrack
#)

# unit tests

find_package(Catch2 3 REQUIRED)

set(TEST_SRCS 
        # 8 bit tests
        tests/cpu/8bitload/ld_r_r.cpp 
        tests/cpu/8bitload/ld_r_n.cpp
        tests/cpu/8bitload/ld_r_hl.cpp
        tests/cpu/8bitload/ld_r_idx.cpp
        tests/cpu/8bitload/ld_hl_r.cpp
        tests/cpu/8bitload/ld_hl_n.cpp
        tests/cpu/registerdecoding.cpp
        tests/cpu/general.cpp
   )

add_executable(tests ${TEST_SRCS} ${CXX_SRCS})

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

target_compile_options(tests PRIVATE -g -std=c++20)
