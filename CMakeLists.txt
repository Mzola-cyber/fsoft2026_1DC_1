cmake_minimum_required(VERSION 3.20)
project(GestaoEncomendas LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
    ${PROJECT_SRC_DIR}/repository/sources/ClienteRepository.cpp
    ${PROJECT_SRC_DIR}/repository/sources/DepositoRepository.cpp
    ${PROJECT_SRC_DIR}/repository/sources/EncomendaRepository.cpp
    ${PROJECT_SRC_DIR}/repository/sources/VeiculoRepository.cpp
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
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Provide include root so sources can use: #include "controller/Sistema.h"
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SRC_DIR})

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
endif()

add_custom_target(run
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Executando ${PROJECT_NAME}..."
)

message(STATUS "Projeto ${PROJECT_NAME} configurado com sucesso")
message(STATUS "C++: ${CMAKE_CXX_STANDARD}")
