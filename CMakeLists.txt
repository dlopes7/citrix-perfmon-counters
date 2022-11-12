cmake_minimum_required(VERSION 3.22)
project(citrix_counters)

include_directories(
        "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.19041.0\\um"
        "C:\\Program Files (x86)\\Windows Kits\\10\\Include\\10.0.22621.0\\shared"
        "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.32.31326\\include"
)

set(CMAKE_CXX_STANDARD 20)
execute_process(COMMAND ctrpp citrix.xml -o citrix_counters.h -rc citrix_counters.rc)

add_executable(citrix_counters
        main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/citrix_counters.rc
        )
