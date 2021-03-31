# cmake最低版本
cmake_minimum_required(VERSION 3.20)

# 啟用IDE目錄功能
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 包括模板
include(CMakePrintHelpers)

# 輸出目錄
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 項目名
project(vector)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/W4;/MP;/Zc:__cplusplus;/std:c17;>")

find_package(Boost REQUIRED)
cmake_print_variables(Boost_FOUND)

add_library(vector INTERFACE)
set_target_properties(vector PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/include"
  INTERFACE_LINK_LIBRARIES "$<$<TARGET_EXISTS:Boost::headers>:Boost::headers>"
  INTERFACE_COMPILE_DEFINITIONS "$<$<TARGET_EXISTS:Boost::headers>:HAS_BOOST>"
)

# 生成執行文件
set(main main)
add_executable(${main})

target_sources(${main}
  PRIVATE
    src/main.cpp
    include/lite/vector.hpp
)

target_include_directories(${main} PRIVATE include)

target_compile_features(${main} PRIVATE cxx_std_17)

# 如果找到Catch2就添加測試
find_package(Catch2 CONFIG)
cmake_print_variables(Catch2_FOUND)

if(Catch2_FOUND)
  set(test test)
  add_executable(${test})
  target_sources(${test}
    PRIVATE
    src/test.cpp
    include/lite/vector.hpp
  )
  target_link_libraries(${test}
    PUBLIC Catch2::Catch2 vector)
  target_compile_features(${test} PRIVATE cxx_std_17)
endif()
