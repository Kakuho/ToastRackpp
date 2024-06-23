cmake_minimum_required(VERSION 3.1...3.29)

project(ToastRackpp LANGUAGES CXX)

include_directories(src)

add_executable(toastrack
               src/main.cpp 
               src/cpu/z80.cpp src/cpu/z80registers.cpp 
               src/loader/baseLoader.cpp src/loader/z80loader.cpp src/loader/taploader.cpp
              )

target_compile_features(toastrack PUBLIC cxx_std_20)

set_target_properties(toastrack PROPERTIES CXX_EXTENSIONS OFF)

add_custom_command(
    TARGET toastrack
    POST_BUILD
    COMMAND toastrack
)
