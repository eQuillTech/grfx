cmake_minimum_required(VERSION 3.10) # required
project(grfx)  # project name

# Enable Xcode dependency analysis for script phases
if(CMAKE_GENERATOR STREQUAL "Xcode")
    set(CMAKE_XCODE_ATTRIBUTE_ENABLE_SCRIPT_PHASE_DEPENDENCY_ANALYSIS YES)
endif()

if(${CMAKE_PROJECT_NAME} STREQUAL "${PROJECT_NAME}")
    set(modules_dir "")
else()
    set(modules_dir "${CMAKE_SOURCE_DIR}/")
endif()

# grfx2
file(GLOB_RECURSE cpp_headers2 CONFIGURE_DEPENDS ${PROJECT_NAME}2/headers/*.hpp)
file(GLOB_RECURSE cpp_sources2 CONFIGURE_DEPENDS ${PROJECT_NAME}2/sources/*.cpp)
set(cpp_srcs2 ${PROJECT_NAME}2/${PROJECT_NAME}2.hpp ${cpp_headers2} ${cpp_sources2})
add_library(${PROJECT_NAME}2 STATIC ${cpp_srcs2})
target_link_libraries(${PROJECT_NAME}2 PUBLIC tlbx arr weiss)
target_include_directories(${PROJECT_NAME}2
    PUBLIC
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}2 ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}2/headers
        ${modules_dir}tlbx ${modules_dir}tlbx/headers
        ${modules_dir}arr ${modules_dir}arr/headers
        ${modules_dir}weiss ${modules_dir}weiss/weiss2 ${modules_dir}weiss/weiss2/headers ${modules_dir}weiss/weiss3 ${modules_dir}weiss/weiss3/headers)
target_compile_features(${PROJECT_NAME}2 PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME}2 PROPERTIES LINKER_LANGUAGE CXX)

# grfx3
file(GLOB_RECURSE cpp_headers3 CONFIGURE_DEPENDS ${PROJECT_NAME}3/headers/*.hpp)
file(GLOB_RECURSE cpp_sources3 CONFIGURE_DEPENDS ${PROJECT_NAME}3/sources/*.cpp)
set(cpp_srcs3 ${PROJECT_NAME}3/${PROJECT_NAME}3.hpp ${cpp_headers3} ${cpp_sources3})
add_library(${PROJECT_NAME}3 STATIC ${cpp_srcs3})
target_link_libraries(${PROJECT_NAME}3 PUBLIC tlbx arr weiss)
target_include_directories(${PROJECT_NAME}3
    PUBLIC
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}3 ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}3/headers
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}2 ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}2/headers
        ${modules_dir}tlbx ${modules_dir}tlbx/headers
        ${modules_dir}arr ${modules_dir}arr/headers
        ${modules_dir}weiss ${modules_dir}weiss/weiss2 ${modules_dir}weiss/weiss2/headers ${modules_dir}weiss/weiss3 ${modules_dir}weiss/weiss3/headers)
target_compile_features(${PROJECT_NAME}3 PRIVATE cxx_std_17)
set_target_properties(${PROJECT_NAME}3 PROPERTIES LINKER_LANGUAGE CXX)

# grfx (header-only library)
add_library(${PROJECT_NAME} INTERFACE)
target_link_libraries(${PROJECT_NAME}
    INTERFACE ${PROJECT_NAME}2 ${PROJECT_NAME}3)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}2 ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}2/headers 
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}3 ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}3/headers)

# submodules
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    add_subdirectory(tlbx)
    add_subdirectory(arr)
    add_subdirectory(weiss)
endif()

# testing
option(${PROJECT_NAME}_BUILD_TESTING "Build the testing tree" ON)
if (${PROJECT_NAME}_BUILD_TESTING)
    # Only add googletest if tlbx is the main project
    if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
        enable_testing()
        set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
        set(CMAKE_SUPPRESS_REGENERATION ON CACHE BOOL "" FORCE)
        add_subdirectory(googletest)
    endif()
    add_subdirectory(test)
endif()