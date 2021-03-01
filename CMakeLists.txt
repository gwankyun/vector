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

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/W4;/MP;/Zc:__cplusplus;>")

# 生成執行文件
set(vector vector)
add_executable(${vector})

target_sources(${vector}
  PRIVATE
    src/main.cpp
    include/lite/vector.hpp
)

target_compile_features(${vector} PRIVATE cxx_std_17)

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
  target_include_directories(${test} PUBLIC include)
  target_link_libraries(${test}
    PUBLIC Catch2::Catch2)
  target_compile_features(${test} PRIVATE cxx_std_17)
endif()
