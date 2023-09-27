cmake_minimum_required(VERSION 3.0)
project(PrometheusCPPClientExample)

# 设置C++标准版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置编译器为32位
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")

# 指定Prometheus C++库的路径
set(PROMETHEUS_CPP_PATH "./third_party/prometheus/32bit")
# set(PROMETHEUS_CPP_PATH "./third_party/prometheus/64bit")

# 导入Prometheus C++库的包含目录
find_package(prometheus-cpp REQUIRED HINTS ${PROMETHEUS_CPP_PATH})
# set(compiler_flags "-m32 -pthread -Werror -fstack-protector -ggdb")
set(compiler_flags "-pthread -Werror -fstack-protector -ggdb")

# 添加可执行文件
add_executable(main main.cpp)

# 链接Prometheus C++库的静态链接库
# target_link_libraries(main prometheus-cpp::pull prometheus-cpp::core -pthread)
target_link_libraries(main prometheus-cpp::pull prometheus-cpp::core)
