cmake_minimum_required(VERSION 3.16)
project(PrometheusCPPClientExample)

# 设置C++标准版本
set(c_compiler_flags "-std=c17")
set(cpp_compiler_flags "-std=c++17")

# set(compiler_flags "-m32 -pthread -Werror -fstack-protector -ggdb")
set(compiler_flags "-m32 -pthread -Werror -fstack-protector -ggdb")

# Statically link libstdc++ and libgcc, so runtime environment has no need to install these depdendencies
set(linker_flags "-static-libstdc++ -static-libgcc")

if (CMAKE_BUILD_TYPE MATCHES "Debug")
  message(STATUS "main: Using compiler flag -pg")
  set(compiler_flags "${compiler_flags} -pg")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${c_compiler_flags} ${compiler_flags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${cpp_compiler_flags} ${compiler_flags}")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${linker_flags}")

# Sets project root dir
set(project_root_dir ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "project_root_dir: " ${project_root_dir})

# Sets root include dir
include_directories(${project_root_dir}/include)

set(SRC_LIST
  main.cpp
)

# 添加可执行文件
add_executable(main ${SRC_LIST})

target_link_libraries(main common)

add_subdirectory(common)
