cmake_minimum_required(VERSION 3.20)
project(GestaoEncomendas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(GestaoEncomendas
    src/main.cpp
    src/controller/Sistema.cpp
        src/domain/sources/Cliente.cpp
        src/domain/sources/Encomenda.cpp
        src/domain/sources/Veiculo.cpp
        src/domain/sources/Deposito.cpp
    src/service/Recomendacao.cpp
)

target_include_directories(GestaoEncomendas PRIVATE
        src/domain/headers)
