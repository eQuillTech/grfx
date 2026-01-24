cmake_minimum_required(VERSION 3.10) # required
project(TopoMesh)  # project name

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    set(modules_dir "")
else()
    set(modules_dir "${CMAKE_SOURCE_DIR}/")
endif()

#
file(GLOB_RECURSE cpp_headers CONFIGURE_DEPENDS headers/*.hpp)
file(GLOB_RECURSE cpp_sources CONFIGURE_DEPENDS sources/*.cpp)
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
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
source_group("headers" FILES ${cpp_headers})
source_group("sources" FILES ${cpp_sources})
source_group("" FILES ${PROJECT_NAME}.hpp)

# submodules
foreach(subdir tlbx arr weiss grfx)
    if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME} OR NOT TARGET ${subdir})
        add_subdirectory(${subdir})
    endif()
endforeach()

# testing
option(${PROJECT_NAME}_BUILD_TESTING "Build the testing tree" ON)
if (${PROJECT_NAME}_BUILD_TESTING)
    # Only add googletest if ${PROJECT_NAME} is the main project
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

add_subdirectory(TriCalc)