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

set_target_properties(vector PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_SOURCE_DIR}/include>;$<INSTALL_INTERFACE:include>"
  INTERFACE_LINK_LIBRARIES "$<$<TARGET_EXISTS:Boost::headers>:Boost::headers>"
  INTERFACE_COMPILE_DEFINITIONS "$<$<TARGET_EXISTS:Boost::headers>:HAS_BOOST>"
)

# install the target and create export-set
install(TARGETS vector
        EXPORT vectorTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

# install header file
install(FILES include/lite/vector.hpp DESTINATION include/lite)

# generate and install export file
install(EXPORT vectorTargets
        FILE vectorTargets.cmake
        NAMESPACE vector::
        DESTINATION lib/cmake/vector
)

# include CMakePackageConfigHelpers macro
include(CMakePackageConfigHelpers)

# set version
set(version 0.0.1)

set_property(TARGET vector PROPERTY VERSION ${version})
set_property(TARGET vector PROPERTY SOVERSION 0)
set_property(TARGET vector PROPERTY
  INTERFACE_vector_MAJOR_VERSION 0)
set_property(TARGET vector APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING vector_MAJOR_VERSION
)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/vectorConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion
)

# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/vectorConfig.cmake"
  INSTALL_DESTINATION lib/cmake/vector
)

# install config files
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/vectorConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/vectorConfigVersion.cmake"
  DESTINATION lib/cmake/vector
)

# generate the export targets for the build tree
export(EXPORT vectorTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/vectorTargets.cmake"
  NAMESPACE vector::
)

set(main main)
add_executable(${main})
target_sources(${main}
  PRIVATE
    src/main.cpp
    include/lite/vector.hpp
)
target_link_libraries(${main} PUBLIC vector)
target_include_directories(${main} PRIVATE include)
target_compile_features(${main} PRIVATE cxx_std_17)

set(test test)
find_package(Catch2 REQUIRED)
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
