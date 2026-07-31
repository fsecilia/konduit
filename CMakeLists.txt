# SPDX-License-Identifier: MIT
# Copyright (c) 2026 Frank Secilia

cmake_minimum_required(VERSION 3.31.6)
project(konduit VERSION 0.1.0 LANGUAGES C CXX)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

find_package(kontraband 0.2 CONFIG REQUIRED)

add_library(konduit_core INTERFACE)
add_library(konduit::core ALIAS konduit_core)

kontra_target_sources(konduit_core INTERFACE
    include/konduit/byte_view.hpp
)
kontra_target_include_directories(konduit_core INTERFACE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
set_target_properties(konduit_core PROPERTIES EXPORT_NAME core)
kontra_install_kernel_payload(konduit_core)
kontra_dump_target(konduit_core)

add_library(konduit_stream STATIC)
add_library(konduit::stream ALIAS konduit_stream)

target_compile_features(konduit_stream PUBLIC cxx_std_20)

kontra_target_sources(konduit_stream PRIVATE
    src/record_encoder.cpp
)

target_sources(konduit_stream PRIVATE
    include/konduit/file_sink.hpp
    src/file_sink.cpp
)

kontra_target_kernel_sources(konduit_stream PRIVATE
    kernel/device_sink.c
    kernel/device_sink.h
)

target_include_directories(konduit_stream PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

kontra_target_kernel_include_directories(konduit_stream PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/kernel"
)

kontra_target_link_libraries(konduit_stream PUBLIC
    konduit_core
)

set_target_properties(konduit_stream PROPERTIES EXPORT_NAME stream)
kontra_install_kernel_payload(konduit_stream)
kontra_dump_target(konduit_stream)

install(
    TARGETS
        konduit_core
        konduit_stream
    EXPORT konduitTargets
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)

install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

set(konduit_cmake_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/konduit")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/konduitConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/konduitConfig.cmake"
    INSTALL_DESTINATION "${konduit_cmake_install_dir}"
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/konduitConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)

install(
    EXPORT konduitTargets
    FILE konduitTargets.cmake
    NAMESPACE konduit::
    DESTINATION "${konduit_cmake_install_dir}"
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/konduitConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/konduitConfigVersion.cmake"
    DESTINATION "${konduit_cmake_install_dir}"
)
