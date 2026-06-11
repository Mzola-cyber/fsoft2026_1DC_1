//
// Created by masem on 11/06/2026.
//

#ifndef GESTAOENCOMENDAS_CLIENTESERVICE_H
#define GESTAOENCOMENDAS_CLIENTESERVICE_H

#pragma once
#include "repository/headers/ClienteRepository.h"
#include "repository/headers/EncomendaRepository.h"
#include "mappers/headers/ClienteMapper.h"
#include "dtos/headers/ClienteOutDto.h"
#include "dtos/headers/ClienteInDto.h"

class ClienteService {
private:
    ClienteRepository& clientesRepository;
    EncomendaRepository& encomendaRepository;

public:
    ClienteService(ClienteRepository& c, EncomendaRepository& e);

    bool removerCliente(int idCliente);
    ClienteOutDto registarCliente(const ClienteInDto& dto);
};

#endif //GESTAOENCOMENDAS_CLIENTESERVICE_H