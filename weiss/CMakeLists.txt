cmake_minimum_required(VERSION 3.10) # required
project(weiss)  # project name

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    set(modules_dir "")
else()
    set(modules_dir "${CMAKE_SOURCE_DIR}/")
endif()

# weiss2
file(GLOB_RECURSE cpp_headers2 weiss2/headers/*.hpp)
file(GLOB_RECURSE cpp_sources2 weiss2/sources/*.cpp)
set(cpp_srcs2 weiss2/weiss2.hpp ${cpp_headers2} ${cpp_sources2})
add_library(weiss2 STATIC ${cpp_srcs2})
target_link_libraries(weiss2 PRIVATE tlbx arr)
target_include_directories(weiss2
    PUBLIC
        ${PROJECT_SOURCE_DIR}/weiss2 ${PROJECT_SOURCE_DIR}/weiss2/headers
    PRIVATE
        ${modules_dir}tlbx ${modules_dir}tlbx/headers
        ${modules_dir}arr ${modules_dir}arr/headers)
target_compile_features(weiss2 PRIVATE cxx_std_17)
set_target_properties(weiss2 PROPERTIES LINKER_LANGUAGE CXX)

# weiss3
file(GLOB_RECURSE cpp_headers3 weiss3/headers/*.hpp)
file(GLOB_RECURSE cpp_sources3 weiss3/sources/*.cpp)
set(cpp_srcs3 weiss3/weiss3.hpp ${cpp_headers3} ${cpp_sources3})
add_library(weiss3 STATIC ${cpp_srcs3})
target_link_libraries(weiss3 PRIVATE tlbx arr)
target_include_directories(weiss3
    PUBLIC
        ${PROJECT_SOURCE_DIR}/weiss2 ${PROJECT_SOURCE_DIR}/weiss2/headers
        ${PROJECT_SOURCE_DIR}/weiss3 ${PROJECT_SOURCE_DIR}/weiss3/headers
    PRIVATE
        ${modules_dir}tlbx ${modules_dir}tlbx/headers
        ${modules_dir}arr ${modules_dir}arr/headers)
target_compile_features(weiss3 PRIVATE cxx_std_17)
set_target_properties(weiss3 PROPERTIES LINKER_LANGUAGE CXX)

# weiss
set(cpp_srcs weiss.hpp weiss2/weiss2.hpp weiss3/weiss3.hpp)
add_library(${PROJECT_NAME} STATIC ${cpp_srcs})
target_link_libraries(weiss PUBLIC weiss2 weiss3)
target_include_directories(weiss
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/weiss2 ${PROJECT_SOURCE_DIR}/weiss2/headers
        ${PROJECT_SOURCE_DIR}/weiss3 ${PROJECT_SOURCE_DIR}/weiss3/headers
    PRIVATE
        ${modules_dir}tlbx ${modules_dir}tlbx/headers
        ${modules_dir}arr ${modules_dir}arr/headers)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# submodules
message(STATUS "project ${CMAKE_PROJECT_NAME}")
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    add_subdirectory(tlbx)
    add_subdirectory(arr)
endif()