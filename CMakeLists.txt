# cmake最低版本
cmake_minimum_required(VERSION 3.21)

# 啟用IDE目錄功能
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 包括模板
include(CMakePrintHelpers)

# 輸出目錄
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# 項目名
project(vector)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH}
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(common)

# 編譯器選項
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/W4;/MP;/Zc:__cplusplus;/std:c17;/experimental:module;>")

find_package(Boost)
cmake_print_variables(Boost_FOUND)

add_library(vector INTERFACE)

set(target vector)

include(GNUInstallDirs)

install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/lite" DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

target_include_directories(${target}
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include;$<$<BOOL:${Boost_FOUND}>:${Boost_INCLUDE_DIR}>>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR};$<$<BOOL:${Boost_FOUND}>:${Boost_INCLUDE_DIR}>>"
)

target_sources(${target}
  INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/lite/vector.cppm>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/lite/vector.cppm>"
)

target_compile_definitions(${target}
  INTERFACE
    "$<$<BOOL:${Boost_FOUND}>:HAS_BOOST>"
)

target_install(${target} "0.0.1")

find_package(Catch2 REQUIRED)
find_package(ztest)
cmake_print_variables(ztest_FOUND)

if(NOT ztest_FOUND)
  add_subdirectory(ztest)
  add_library(ztest::ztest ALIAS ztest)
endif()

set(main main)
add_executable(${main})
target_sources(${main}
  PRIVATE
    src/main.cpp
    src/main.cppm
    include/lite/vector.cppm
    cmake/vectorConfig.cmake.in
)
target_link_libraries(${main} PUBLIC vector ztest::ztest)
target_include_directories(${main} PRIVATE include)
target_compile_features(${main} PRIVATE cxx_std_20)

# set(test test)
# if(Catch2_FOUND)
#   add_executable(${test})
#   target_sources(${test}
#     PRIVATE
#     src/test.cpp
#     include/lite/vector.hpp
#   )
#   target_link_libraries(${test}
#     PUBLIC Catch2::Catch2 vector)
#   target_compile_features(${test} PRIVATE cxx_std_17)
# endif()
