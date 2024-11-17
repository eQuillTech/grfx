cmake_minimum_required(VERSION 3.10) # required
project(grfx)  # project name

# grfx2
file(GLOB_RECURSE cpp_headers2 grfx2/headers/*.hpp)
file(GLOB_RECURSE cpp_sources2 grfx2/sources/*.cpp)
set(cpp_srcs2 grfx2/grfx2.hpp ${cpp_headers2} ${cpp_sources2})
add_library(grfx2 STATIC ${cpp_srcs2})
target_link_libraries(grfx2 PRIVATE tlbx arr)
target_include_directories(grfx2 PUBLIC . grfx2 grfx2/headers tlbx arr weiss)
target_compile_features(grfx2 PRIVATE cxx_std_17)
set_target_properties(grfx2 PROPERTIES LINKER_LANGUAGE CXX)

# grfx3
file(GLOB_RECURSE cpp_headers3 grfx3/headers/*.hpp)
file(GLOB_RECURSE cpp_sources3 grfx3/sources/*.cpp)
set(cpp_srcs3 grfx3/grfx3.hpp ${cpp_headers3} ${cpp_sources3})
add_library(grfx3 STATIC ${cpp_srcs3})
target_link_libraries(grfx3 PRIVATE tlbx arr weiss)
target_include_directories(grfx3 PUBLIC . grfx3 grfx3/headers tlbx arr weiss)
target_compile_features(grfx3 PRIVATE cxx_std_17)
set_target_properties(grfx3 PROPERTIES LINKER_LANGUAGE CXX)

# grfx
set(cpp_srcs grfx.hpp grfx2/grfx2.hpp grfx3/grfx3.hpp)
add_library(grfx STATIC ${cpp_srcs})
target_link_libraries(grfx PUBLIC grfx2 grfx3)
target_include_directories(grfx PUBLIC . grfx2 grfx2/headers grfx3 grfx3/headers tlbx arr weiss)
target_compile_features(grfx PRIVATE cxx_std_17)
set_target_properties(grfx PROPERTIES LINKER_LANGUAGE CXX)

# submodules
message(STATUS "project ${CMAKE_PROJECT_NAME}")
if(${CMAKE_PROJECT_NAME} STREQUAL "grfx")
    message(STATUS "adding tlbx")
    add_subdirectory(tlbx)
endif()

if("${CMAKE_PROJECT_NAME}" STREQUAL "grfx")
    message(STATUS "adding arr")
    add_subdirectory(arr)
endif()

if("${CMAKE_PROJECT_NAME}" STREQUAL "grfx")
    message(STATUS "adding weiss")
    add_subdirectory(weiss)
endif()