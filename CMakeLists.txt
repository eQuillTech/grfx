cmake_minimum_required(VERSION 3.10) # required
project(TopoMesh)  # project name

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    set(modules_dir "")
else()
    set(modules_dir "${CMAKE_SOURCE_DIR}/")
endif()

#
file(GLOB_RECURSE cpp_headers headers/*.hpp)
file(GLOB_RECURSE cpp_sources sources/*.cpp)
set(cpp_srcs ${PROJECT_NAME}.hpp ${cpp_headers} ${cpp_sources})
add_library(${PROJECT_NAME} STATIC ${cpp_srcs})
target_link_libraries(${PROJECT_NAME} PUBLIC weiss grfx)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/headers
    PRIVATE
        ${modules_dir}weiss ${modules_dir}weiss/weiss2 ${modules_dir}weiss/weiss2/headers ${modules_dir}weiss/weiss3 ${modules_dir}weiss/weiss3/headers
        ${modules_dir}grfx ${modules_dir}grfx/grfx2 ${modules_dir}grfx/grfx2/headers ${modules_dir}grfx/grfx3 ${modules_dir}grfx/grfx3/headers)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

# submodules
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    message(STATUS "adding weiss")
    add_subdirectory(${modules_dir}weiss)
endif()

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    message(STATUS "adding grfx")
    add_subdirectory(${modules_dir}grfx)
endif()

