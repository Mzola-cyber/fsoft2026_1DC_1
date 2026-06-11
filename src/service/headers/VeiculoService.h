//
// Created by masem on 11/06/2026.
//

#ifndef GESTAOENCOMENDAS_VEICULOSERVICE_H
#define GESTAOENCOMENDAS_VEICULOSERVICE_H

#pragma once
#include "repository/headers/VeiculoRepository.h"
#include "repository/headers/EncomendaRepository.h"
#include "dtos/headers/VeiculoInDto.h"
#include "dtos/headers/VeiculoOutDto.h"
#include "mappers/headers/VeiculoMapper.h"

class VeiculoService {
private:
    VeiculoRepository& veiculosRepository;
    EncomendaRepository& encomendaRepository;

public:
    VeiculoService(VeiculoRepository& v, EncomendaRepository& e);

    bool removerVeiculo(int idVeiculo);
    VeiculoOutDto adicionarVeiculo(const VeiculoInDto& dto);
};

#endif //GESTAOENCOMENDAS_VEICULOSERVICE_H