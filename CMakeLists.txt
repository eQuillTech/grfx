cmake_minimum_required(VERSION 3.10) # required
project(grfx)  # project name

if(${CMAKE_PROJECT_NAME} STREQUAL "grfx")
    set(modules_dir "")
else()
    set(modules_dir "${CMAKE_SOURCE_DIR}/")
endif()

# grfx2
file(GLOB_RECURSE cpp_headers2 grfx2/headers/*.hpp)
file(GLOB_RECURSE cpp_sources2 grfx2/sources/*.cpp)
set(cpp_srcs2 grfx2/grfx2.hpp ${cpp_headers2} ${cpp_sources2})
add_library(grfx2 STATIC ${cpp_srcs2})
target_link_libraries(grfx2 PRIVATE tlbx arr)
target_include_directories(grfx2
    PUBLIC
        ${PROJECT_SOURCE_DIR}/grfx2 ${PROJECT_SOURCE_DIR}/grfx2/headers
    PRIVATE
        ${modules_dir}tlbx ${modules_dir}tlbx/headers
        ${modules_dir}arr ${modules_dir}arr/headers
        ${modules_dir}weiss ${modules_dir}weiss/weiss2 ${modules_dir}weiss/weiss2/headers ${modules_dir}weiss/weiss3 ${modules_dir}weiss/weiss3/headers)
target_compile_features(grfx2 PRIVATE cxx_std_17)
set_target_properties(grfx2 PROPERTIES LINKER_LANGUAGE CXX)

# grfx3
file(GLOB_RECURSE cpp_headers3 grfx3/headers/*.hpp)
file(GLOB_RECURSE cpp_sources3 grfx3/sources/*.cpp)
set(cpp_srcs3 grfx3/grfx3.hpp ${cpp_headers3} ${cpp_sources3})
add_library(grfx3 STATIC ${cpp_srcs3})
target_link_libraries(grfx3 PRIVATE tlbx arr weiss)
target_include_directories(grfx3
    PUBLIC
        ${PROJECT_SOURCE_DIR}/grfx3 ${PROJECT_SOURCE_DIR}/grfx3/headers
    PRIVATE
        ${PROJECT_SOURCE_DIR}/grfx2 ${PROJECT_SOURCE_DIR}/grfx2/headers
        ${modules_dir}tlbx ${modules_dir}tlbx/headers
        ${modules_dir}arr ${modules_dir}arr/headers
        ${modules_dir}weiss ${modules_dir}weiss/weiss2 ${modules_dir}weiss/weiss2/headers ${modules_dir}weiss/weiss3 ${modules_dir}weiss/weiss3/headers)
target_compile_features(grfx3 PRIVATE cxx_std_17)
set_target_properties(grfx3 PROPERTIES LINKER_LANGUAGE CXX)

# grfx
set(cpp_srcs grfx.hpp defs.hpp grfx2/grfx2.hpp grfx3/grfx3.hpp)
add_library(grfx STATIC ${cpp_srcs})
target_link_libraries(grfx PUBLIC grfx2 grfx3)
target_include_directories(grfx
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/grfx2 ${PROJECT_SOURCE_DIR}/grfx2/headers 
        ${PROJECT_SOURCE_DIR}/grfx3 ${PROJECT_SOURCE_DIR}/grfx3/headers
    PRIVATE
        ${modules_dir}tlbx ${modules_dir}tlbx/headers
        ${modules_dir}arr ${modules_dir}arr/headers
        ${modules_dir}weiss ${modules_dir}weiss/weiss2 ${modules_dir}weiss/weiss2/headers ${modules_dir}weiss/weiss3 ${modules_dir}weiss/weiss3/headers)
target_compile_features(grfx PRIVATE cxx_std_17)
set_target_properties(grfx PROPERTIES LINKER_LANGUAGE CXX)

# submodules
message(STATUS "project ${CMAKE_PROJECT_NAME}")
if(${CMAKE_PROJECT_NAME} STREQUAL "grfx")
    add_subdirectory(tlbx)
    add_subdirectory(arr)
    add_subdirectory(weiss)
endif()