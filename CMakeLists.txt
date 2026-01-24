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

# Enable folder organization in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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
set_target_properties(${PROJECT_NAME}2 PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER ${PROJECT_NAME})
source_group("headers" FILES ${cpp_headers2})
source_group("sources" FILES ${cpp_sources2})
source_group("" FILES ${PROJECT_NAME}2/${PROJECT_NAME}2.hpp)

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
set_target_properties(${PROJECT_NAME}3 PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER ${PROJECT_NAME})
source_group("headers" FILES ${cpp_headers3})
source_group("sources" FILES ${cpp_sources3})
source_group("" FILES ${PROJECT_NAME}3/${PROJECT_NAME}3.hpp)

# grfx (header-only library)
add_library(${PROJECT_NAME} INTERFACE ${PROJECT_NAME}.hpp)
target_link_libraries(${PROJECT_NAME}
    INTERFACE ${PROJECT_NAME}2 ${PROJECT_NAME}3)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}2 ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}2/headers 
        ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}3 ${PROJECT_SOURCE_DIR}/${PROJECT_NAME}3/headers)
source_group("" FILES ${PROJECT_NAME}.hpp)

# submodules
foreach(subdir tlbx arr weiss)
    if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME} OR NOT TARGET ${subdir})
        add_subdirectory(${subdir})
    endif()
endforeach()

# testing
option(${PROJECT_NAME}_BUILD_TESTING "Build the testing tree" ON)
if (${PROJECT_NAME}_BUILD_TESTING)
    # Only add googletest if tlbx is the main project
    if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
        enable_testing()
        set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
        set(CMAKE_SUPPRESS_REGENERATION ON CACHE BOOL "" FORCE)
        add_subdirectory(googletest)
        
        # Organize gtest_main inside gtest folder
        if(TARGET gtest_main)
            set_target_properties(gtest_main PROPERTIES FOLDER "gtest")
        endif()
    endif()
    add_subdirectory(test)
endif()