//
// Created by Mário Figueira on 02/06/2026.
//

#ifndef GESTAOENCOMENDAS_ADMINISTRADORVIEW_H
#define GESTAOENCOMENDAS_ADMINISTRADORVIEW_H
#include <vector>
#include "../../dtos/headers/DepositoInDto.h"
#include "../../dtos/headers/DepositoOutDto.h"
#include "../../dtos/headers/VeiculoInDto.h"
#include "../../dtos/headers/VeiculoOutDto.h"
#include "../../dtos/headers/ClienteOutDto.h"
#include "../../dtos/headers/EncomendaOutDto.h"

class AdministradorView {
public:
    AdministradorView();

    DepositoInDto getDeposito();
    VeiculoInDto getVeiculo();

    int getIdCliente();
    int getIdVeiculo();
    int getIdEncomenda();

    void printDeposito(const DepositoOutDto& deposito);
    void printVeiculo(const VeiculoOutDto& veiculo);

    void printClientes(const std::vector<ClienteOutDto>& clientes);
    void printDepositos(const std::vector<DepositoOutDto>& depositos);
    void printVeiculos(const std::vector<VeiculoOutDto>& veiculos);
    void printEncomendas(const std::vector<EncomendaOutDto>& encomendas);
};

#endif

