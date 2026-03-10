cmake_minimum_required(VERSION 3.20)
project(SwiftCPP LANGUAGES CXX)

# Устанавливаем стандарт C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Добавляем исполняемый файл из одного исходника
add_executable(myapp core/core.cpp core/main.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sample.png 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# Включаем оптимизации и предупреждения (опционально)
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(myapp PRIVATE -O3 -DNDEBUG)
else()
    target_compile_options(myapp PRIVATE -O0 -g -Wall -Wextra -Wpedantic)
endif() 