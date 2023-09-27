cmake_minimum_required(VERSION 3.16)
project(PrometheusCPPClientExample)

# 设置C++标准版本
set(c_compiler_flags "-std=c17")
set(cpp_compiler_flags "-std=c++17")

# 设置编译器为32位
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
# 设置编译器为64位
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")

include_directories("./include")

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

set(SRC_LIST
  main.cpp
)

string(FIND "${CMAKE_CXX_FLAGS}" "-m32" IS_32_BIT)
if(IS_32_BIT GREATER -1)
  # prometheus_x86
  set(PROMETHEUS_CPP_PATH "./third_party/prometheus/x86")
  message("-- use prometheus_x86")
else()
  # prometheus_x86_64
  set(PROMETHEUS_CPP_PATH "./third_party/prometheus/x86_64")
  message("-- use prometheus_x86_64")
endif()

# 导入Prometheus C++库的包含目录
find_package(prometheus-cpp REQUIRED HINTS ${PROMETHEUS_CPP_PATH})

# 添加可执行文件
add_executable(main ${SRC_LIST})

target_link_libraries(main common)

add_subdirectory(source)
