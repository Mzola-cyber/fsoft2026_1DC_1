cmake_minimum_required(VERSION 4.1)
project(GestaoEncomendas)

set(CMAKE_CXX_STANDARD 20)

# Include directories - allows includes relative to src/
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Project directories
set(PROJECT_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_DOMAIN_HEADERS_DIR ${PROJECT_SRC_DIR}/domain/headers)
set(PROJECT_DOMAIN_SOURCES_DIR ${PROJECT_SRC_DIR}/domain/sources)
set(PROJECT_CONTROLLER_DIR ${PROJECT_SRC_DIR}/controller)
set(PROJECT_SERVICE_DIR ${PROJECT_SRC_DIR}/service)

# Domain sources
set(DOMAIN_SOURCES
        ${PROJECT_DOMAIN_SOURCES_DIR}/Cliente.cpp
        ${PROJECT_DOMAIN_SOURCES_DIR}/Deposito.cpp
        ${PROJECT_DOMAIN_SOURCES_DIR}/Encomenda.cpp
        ${PROJECT_DOMAIN_SOURCES_DIR}/Veiculo.cpp
)

# Repository sources
set(REPOSITORY_SOURCES
        ${PROJECT_SRC_DIR}/repository/sources/DepositoRepository.cpp
        ${PROJECT_SRC_DIR}/repository/sources/ClienteRepository.cpp
        ${PROJECT_SRC_DIR}/repository/sources/VeiculoRepository.cpp
        ${PROJECT_SRC_DIR}/repository/sources/EncomendaRepository.cpp
)

# Controller sources
set(CONTROLLER_SOURCES
        ${PROJECT_CONTROLLER_DIR}/Sistema.cpp
)

# Service sources
set(SERVICE_SOURCES
        ${PROJECT_SERVICE_DIR}/Recomendacao.cpp
)

# Main
set(MAIN_SOURCE ${PROJECT_SRC_DIR}/main.cpp)

# All sources
set(SOURCES
        ${MAIN_SOURCE}
        ${CONTROLLER_SOURCES}
        ${DOMAIN_SOURCES}
        ${REPOSITORY_SOURCES}
        ${SERVICE_SOURCES}
)

# Headers (for IDE convenience)
set(HEADERS
        ${PROJECT_CONTROLLER_DIR}/Sistema.h
        ${PROJECT_DOMAIN_HEADERS_DIR}/Cliente.h
        ${PROJECT_DOMAIN_HEADERS_DIR}/Deposito.h
        ${PROJECT_DOMAIN_HEADERS_DIR}/Encomenda.h
        ${PROJECT_DOMAIN_HEADERS_DIR}/Veiculo.h
        ${PROJECT_SERVICE_DIR}/Recomendacao.h
        ${PROJECT_SRC_DIR}/repository/headers/DepositoRepository.h
        ${PROJECT_SRC_DIR}/repository/headers/ClienteRepository.h
        ${PROJECT_SRC_DIR}/repository/headers/VeiculoRepository.h
        ${PROJECT_SRC_DIR}/repository/headers/EncomendaRepository.h
)


add_executable(GestaoEncomendas main.cpp

        src/controller/Sistema.cpp
        src/controller/Sistema.h


        src/domain/sources/Cliente.cpp
        src/domain/sources/Deposito.cpp
        src/domain/sources/Encomenda.cpp
        src/domain/sources/Veiculo.cpp
        src/domain/headers/Cliente.h
        src/domain/headers/Deposito.h
        src/domain/headers/Encomenda.h
        src/domain/headers/Veiculo.h

        src/repository/sources/ClienteRepository.cpp
        src/repository/sources/DepositoRepository.cpp
        src/repository/sources/EncomendaRepository.cpp
        src/repository/sources/VeiculoRepository.cpp
        src/repository/headers/ClienteRepository.h
        src/repository/headers/DepositoRepository.h
        src/repository/headers/EncomendaRepository.h
        src/repository/headers/VeiculoRepository.h

        src/service/Recomendacao.cpp
        src/service/Recomendacao.h
        src/View/sources/ClienteView.cpp

        src/View/sources/UtilsView.cpp
        src/View/sources/AdministradorView.cpp
        src/mappers/sources/ClienteMapper.cpp
        src/mappers/sources/DepositoMapper.cpp
        src/mappers/sources/EncomendaMapper.cpp
        src/mappers/sources/VeiculoMapper.cpp
)

