
cmake_minimum_required(VERSION 3.10.0)
project(tronicrentals VERSION 0.1.0)

if(NOT(UNIX AND NOT APPLE))
    set(CMAKE_CXX_COMPILER /usr/bin/clang++)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CTest)

# Add the main executable
add_executable(tronicrentals src/main.cpp)

# Add the subdirectories containing the source files
add_subdirectory(src)
add_subdirectory(src/app)
add_subdirectory(test)
add_subdirectory(student_test)

# Define the path to the CTestCustom.cmake file in the build directory
set(CTEST_CUSTOM_FILE "${CMAKE_BINARY_DIR}/CTestCustom.cmake")
# Use a large value for the maximum passed test output size so it isn't truncated
file(WRITE ${CTEST_CUSTOM_FILE} 
"set(CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE 10240 CACHE INTERNAL \"\")\n")

enable_testing()

# Link the subdirectory targets to the main executable
target_link_libraries(tronicrentals SrcTarget SrcAppSupportTarget)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
