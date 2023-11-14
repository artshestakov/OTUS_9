cmake_minimum_required(VERSION 3.12)

project(bulk)

set (CMAKE_CXX_STANDARD 17)
find_package(Threads)

IF (WIN32)
    set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
ENDIF()


add_library(async SHARED
    src/libasync/async.cpp
    src/libasync/async.h
)

add_executable(bulk
    src/bulk/main.cpp
    src/bulk/cmd.cpp
    src/bulk/writers.cpp
    src/bulk/writer_thread.cpp
    src/bulk/observer.h
    src/bulk/stdafx.h
)

target_include_directories(bulk PRIVATE
    ${CMAKE_BINARY_DIR}/../src/bulk
    ${CMAKE_BINARY_DIR}/../src/libasync
)

target_link_libraries(bulk async)

install(TARGETS bulk RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_FILE_NAME "bulk")
set(CPACK_PACKAGE_CONTACT art.shestakov@icloud.com)
include(CPack)
