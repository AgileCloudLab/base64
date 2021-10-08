cmake_minimum_required(VERSION 3.10)

project(base64 VERSION 1.0.0 DESCRIPTION "A simple base64 container encoder for C++" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")

add_library(base64 INTERFACE)
target_include_directories(base64 INTERFACE src/base64)

# Downloading Google Test for CMAKE 
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing

enable_testing()
add_executable(test_base64 ../test/test_base64/test_base64.cpp)
target_include_directories(test_base64 INTERFACE base64)
