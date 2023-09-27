cmake_minimum_required(VERSION 3.16)

include_directories(include)

set(SRC_LIST
  PrometheusMgr.cpp
)

add_library(common STATIC ${SRC_LIST})

# 链接Prometheus C++库的静态链接库
string(FIND "${CMAKE_CXX_FLAGS}" "-m32" IS_32_BIT)
if(IS_32_BIT GREATER -1)
  # prometheus_x86
  set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/prometheus/x86")
  message("-- use prometheus_x86")
else()
  # prometheus_x86_64
  set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/prometheus/x86_64")
  message("-- use prometheus_x86_64")
endif()
# prometheus
set(PROMETHEUS_LIBS
  ${LIB_DIR}/libprometheus-cpp-pull.a
  ${LIB_DIR}/libprometheus-cpp-core.a
)
target_link_libraries(common ${PROMETHEUS_LIBS})
