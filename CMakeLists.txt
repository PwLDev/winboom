cmake_minimum_required(VERSION 3.10)
project(Winboom)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(winboom src/winboom.cpp)
target_link_libraries(winboom ntdll)