cmake_minimum_required(VERSION 3.10)

project(TextAnalyzer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(TextAnalyzer main.cpp)

# Указываем MSVC что исходник в UTF-8
if(MSVC)
    target_compile_options(TextAnalyzer PRIVATE /utf-8)
endif()

install(TARGETS TextAnalyzer DESTINATION bin)
