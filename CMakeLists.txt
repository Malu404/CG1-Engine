cmake_minimum_required(VERSION 3.10)

# Nome do projeto
project(CG1-Engine)

# Definir o padrão do compilador
set(CMAKE_CXX_STANDARD 17)

# Adicionar as flags do compilador
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
endif()

# Incluir as flags do SDL2
set(SDL2_DIR "E:/SDL2/SDL2-2.30.9/cmake")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Adicionar o executável
add_executable(cg1 main.cpp)

# Ligar o SDL2 ao executável
target_link_libraries(cg1 ${SDL2_LIBRARIES})