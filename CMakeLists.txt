cmake_minimum_required(VERSION 3.20)
project(GestaoEncomendas)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(GestaoEncomendas
    src/main.cpp
    src/controller/Sistema.cpp
    src/domain/Cliente.cpp
    src/domain/Encomenda.cpp
    src/domain/Veiculo.cpp
    src/domain/Deposito.cpp
    src/service/Recomendacao.cpp
)