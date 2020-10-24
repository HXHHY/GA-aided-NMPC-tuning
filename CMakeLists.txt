cmake_minimum_required(VERSION 3.18)

project(ga_nmpc_tuning VERSION 0.0)
set(PROJECT_ALIAS "gnt")


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()
message(STATUS "Generating with build type: ${CMAKE_BUILD_TYPE}")

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

set(CMAKE_BINARY_DIR        ${CMAKE_SOURCE_DIR}/_bin)
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH     ${CMAKE_BINARY_DIR}/lib)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/data)

find_package(PkgConfig   REQUIRED)
find_package(yaml-cpp    REQUIRED)
find_package(jsoncpp     REQUIRED)
find_package(Eigen3 3.3  REQUIRED)

pkg_check_modules(libCPPAD  REQUIRED  cppad)
pkg_check_modules(libIPOPT  REQUIRED  ipopt)

set(LINK_DEPS
    yaml-cpp
    jsoncpp
    ${libIPOPT_LIBRARIES}
    ${libCPPAD_LIBRARIES}
    Eigen3::Eigen
)

set(LIB_SOURCES

    src/helloworld.cpp
    
)

set(PRECOMPILED_HEADER include/pch.h)

include_directories("include")

add_library(${PROJECT_ALIAS} ${LIB_SOURCES})
target_link_libraries(${PROJECT_ALIAS} ${LINK_DEPS})
set_target_properties(${PROJECT_ALIAS} PROPERTIES LINKER_LANGUAGE CXX)
target_precompile_headers(${PROJECT_ALIAS} PRIVATE ${PRECOMPILED_HEADER})


add_executable(test_run src/main.cpp)
target_link_libraries(test_run ${PROJECT_ALIAS})
target_precompile_headers(test_run REUSE_FROM ${PROJECT_ALIAS})
