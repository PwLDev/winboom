cmake_minimum_required(VERSION 3.10)
project(Winboom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

add_executable(winboom src/winboom.cpp)
target_link_libraries(winboom ntdll)