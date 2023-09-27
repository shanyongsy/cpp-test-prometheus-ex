cmake_minimum_required(VERSION 3.16)

set(SRC_LIST
  PrometheusMgr.cpp
)

add_library(common STATIC ${SRC_LIST})

# 链接Prometheus C++库的静态链接库
target_link_libraries(common prometheus-cpp::pull prometheus-cpp::core)
