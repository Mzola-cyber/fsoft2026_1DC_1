//
// Created by masem on 11/06/2026.
//

#ifndef GESTAOENCOMENDAS_ENCOMENDASERVICE_H
#define GESTAOENCOMENDAS_ENCOMENDASERVICE_H
#pragma once
#include <string>
#include "domain/headers/Encomenda.h"
#include "repository/headers/EncomendaRepository.h"
#include "repository/headers/ClienteRepository.h"
#include "repository/headers/DepositoRepository.h"
#include "repository/headers/VeiculoRepository.h"

#include "RecomendacaoService.h"
#include "dtos/headers/EncomendaInDto.h"
#include "dtos/headers/EncomendaOutDto.h"

class EncomendaService {

private:
    EncomendaRepository& encomendaRepository;
    ClienteRepository& clientesRepository;
    DepositoRepository& depositosRepository;
    VeiculoRepository& veiculosRepository;

    RecomendacaoService recomendacaoService;

public:
    EncomendaService(
        EncomendaRepository& encRepo,
        ClienteRepository& cliRepo,
        DepositoRepository& depRepo,
        VeiculoRepository& veiRepo
    );

    EncomendaOutDto criarEncomenda(const EncomendaInDto& dto);
    bool avancarEstadoEncomenda(int idEncomenda);
    bool cancelarEncomenda(int idEncomenda);
    [[nodiscard]] std::string consultarEstadoEncomenda(int idEncomenda, int idCliente) const;/// PARA O SISTEMA AO EXECUTAR NAO IGNORAR
    void tentarAtribuirPendentes();
};
#endif //GESTAOENCOMENDAS_ENCOMENDASERVICE_H