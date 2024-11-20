cmake_minimum_required(VERSION 3.10) # required
project(tlbx)  # project name
		
file(GLOB_RECURSE cpp_headers headers/*.hpp)
file(GLOB_RECURSE cpp_sources sources/*.cpp)
set(cpp_srcs ${PROJECT_NAME}.hpp ${cpp_headers} ${cpp_sources})

add_library(${PROJECT_NAME} STATIC ${cpp_srcs})

message(STATUS "project ${CMAKE_PROJECT_NAME}")
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/headers)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
