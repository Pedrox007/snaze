cmake_minimum_required(VERSION 3.5)
project(snaze VERSION 0.1 LANGUAGES CXX )

add_compile_options(-g -Wall -std=c++17)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
### Executável
# Diretório contendo os .hpp
include_directories( include )

# Cria um executável com nome "snaze"
add_executable( snaze
                src/Snaze.cpp
                src/SnakeGame.cpp
                src/Level.cpp
                src/Utils.cpp
                src/Snake.cpp)

# The end
