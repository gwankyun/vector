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

find_package(Boost)
cmake_print_variables(Boost_FOUND)

add_library(vector INTERFACE)

set(target vector)

set_target_properties(${target} PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>;$<$<BOOL:${Boost_FOUND}>:${Boost_INCLUDE_DIR}>"
  INTERFACE_COMPILE_DEFINITIONS "$<$<BOOL:${Boost_FOUND}>:HAS_BOOST>"
)

# install the target and create export-set
install(TARGETS ${target}
  EXPORT vectorTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

# install header file
install(FILES include/lite/vector.hpp DESTINATION include/lite)

# generate and install export file
install(EXPORT ${target}Targets
  FILE ${target}Targets.cmake
  NAMESPACE ${target}::
  DESTINATION lib/cmake/${target}
)

# include CMakePackageConfigHelpers macro
include(CMakePackageConfigHelpers)

# set version
set(version 0.0.1)

set_property(TARGET ${target} PROPERTY VERSION ${version})
set_property(TARGET ${target} PROPERTY SOVERSION 0)
set_property(TARGET ${target} PROPERTY
  INTERFACE_${target}_MAJOR_VERSION 0)
set_property(TARGET ${target} APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING ${target}_MAJOR_VERSION
)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion
)

# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${target}Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${target}Config.cmake"
  INSTALL_DESTINATION lib/cmake/${target}
)

# install config files
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${target}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${target}ConfigVersion.cmake"
  DESTINATION lib/cmake/${target}
)

# generate the export targets for the build tree
export(EXPORT ${target}Targets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${target}Targets.cmake"
  NAMESPACE ${target}::
)

find_package(Catch2 REQUIRED)

set(main main)
add_executable(${main})
target_sources(${main}
  PRIVATE
    src/main.cpp
    src/main.cppm
    include/lite/vector.cppm
)
target_link_libraries(${main} PUBLIC vector Catch2::Catch2)
target_include_directories(${main} PRIVATE include)
target_compile_features(${main} PRIVATE cxx_std_20)
target_compile_options(${main} PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/std:c17;/experimental:module;>")

set(test test)
if(Catch2_FOUND)
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
