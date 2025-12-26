cmake_minimum_required(VERSION 3.10)
project(CalculatorCore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(CalculatorCore SHARED CalculatorCore.cpp)

set_target_properties(CalculatorCore PROPERTIES
    PREFIX ""
    VERSION 1.0.0
    SOVERSION 1
)

# 确保在 macOS 上生成 .dylib
if(APPLE)
    set_target_properties(CalculatorCore PROPERTIES SUFFIX ".dylib")
endif()
