cmake_minimum_required(VERSION 3.14)
project(CANFrameUtils C CXX)

# Enforce C11 and C++17 standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Strict Compiler Flags (Warnings-as-Errors for ASPICE Quality Gate)
if(MSVC)
    add_compile_options(/W4 /WX) # MSVC strict warnings
else()
    add_compile_options(-Wall -Wextra -Werror) # GCC / Clang strict warnings
endif()

# Include directories for source code
include_directories(include src)

# 1. Build the C Library (Static Library)
add_library(can_frame_lib STATIC src/can_frame.c)

# 2. Automatically Fetch Google Test via CMake FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows MSVC runtime compatibility
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable CTest integration
enable_testing()

# 3. Build the Unit Test Executable (C++ Linking with C Library)
add_executable(run_unit_tests tests/test_can_frame.cpp)

# Link the test executable with our C library and Google Test (gtest_main handles main())
target_link_libraries(run_unit_tests PRIVATE can_frame_lib gtest_main)

# Register test with CTest runner
include(GoogleTest)
gtest_discover_tests(run_unit_tests)