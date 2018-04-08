cmake_minimum_required(VERSION 2.8)
add_executable(VMTest VMTest.cpp)
include_directories(${EMU_SOURCE_DIR}/src)
target_link_libraries(VMTest vm)