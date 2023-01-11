cmake_minimum_required(VERSION 3.0.0)
project(Beresta VERSION 0.1.0)

include(CTest)

add_subdirectory(App)

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(Test)
endif ()

enable_testing()

add_executable(Beresta App/src/main.cpp)

SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
    )

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/bin
        CACHE PATH
        "Single Directory for all"
    )

SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
        ${PROJECT_BINARY_DIR}/lib
        CACHE PATH
        "Single Directory for all"
    )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
