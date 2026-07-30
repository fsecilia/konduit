# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.31.6)
project(konduit_consumer LANGUAGES CXX)

find_package(konduit 0.1 CONFIG REQUIRED)

foreach(target IN ITEMS konduit::core konduit::stream)
    if(NOT TARGET "${target}")
        message(FATAL_ERROR "missing imported target ${target}")
    endif()

    get_target_property(component_id "${target}" KONTRA_COMPONENT_ID)
    if(NOT component_id OR component_id MATCHES "NOTFOUND")
        message(FATAL_ERROR "${target} has no Kontraband component id")
    endif()

    get_target_property(kernel_sources "${target}" INTERFACE_KONTRA_KERNEL_SOURCES)
    get_target_property(kernel_files "${target}" INTERFACE_KONTRA_KERNEL_FILES)

    if(NOT kernel_sources OR kernel_sources MATCHES "-NOTFOUND$")
        set(kernel_sources)
    endif()
    if(NOT kernel_files OR kernel_files MATCHES "-NOTFOUND$")
        set(kernel_files)
    endif()

    foreach(file IN LISTS kernel_sources kernel_files)
        if(NOT EXISTS "${file}")
            message(FATAL_ERROR "${target} references missing kernel payload file: ${file}")
        endif()
    endforeach()
endforeach()

get_target_property(stream_dependencies
    konduit::stream
    INTERFACE_KONTRA_KERNEL_DEPENDENCIES)

if(NOT "konduit::core" IN_LIST stream_dependencies)
    message(FATAL_ERROR
        "konduit::stream kernel dependencies were not rewritten through install(EXPORT): "
        "${stream_dependencies}")
endif()

add_executable(konduit_consumer main.cpp)
target_link_libraries(konduit_consumer PRIVATE konduit::stream)
