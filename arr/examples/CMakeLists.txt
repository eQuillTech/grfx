
# Example executable
set(example_sources
        examples.cpp
        )
		
add_executable(examples ${example_sources})
target_include_directories(examples PRIVATE ${CMAKE_SOURCE_DIR}/tlbx)
target_link_libraries(examples PUBLIC ${PROJECT_NAME})

target_compile_features(examples PRIVATE cxx_std_17)
