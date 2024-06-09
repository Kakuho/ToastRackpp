cmake_minimum_required(VERSION 3.1...3.29)

project(ToastRackpp LANGUAGES CXX)

add_executable(toastrack
               src/main.cpp 
               src/48k/cpu/instruction.cpp src/48k/cpu/z80.cpp
               src/loader/baseLoader.cpp src/loader/z80loader.cpp src/loader/taploader.cpp
              )


add_custom_command(
    TARGET toastrack
    POST_BUILD
    COMMAND toastrack
)
