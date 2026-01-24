set(test_headers
        unit-test.hpp
        )

set(test_sources
        TopoMeshTest.cpp
        unit-test-main.cpp
        )

set(files ${test_headers} ${test_sources})

# Organize files into groups for Xcode/Visual Studio
source_group("headers" FILES ${test_headers})
source_group("sources" FILES ${test_sources})

add_executable(${PROJECT_NAME}_tests ${files})

target_compile_features(${PROJECT_NAME}_tests PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME}_tests
    PRIVATE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/headers)

set_target_properties(${PROJECT_NAME}_tests PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}_tests ${PROJECT_NAME} gtest)

# Code sign to avoid macOS permission dialogs
if(APPLE)
    set_target_properties(${PROJECT_NAME}_tests PROPERTIES
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "-"
        XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO"
        XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED "NO"
    )
endif()

include(GoogleTest)

gtest_discover_tests(
        ${PROJECT_NAME}_tests
        TEST_PREFIX ${PROJECT_NAME}:
)
