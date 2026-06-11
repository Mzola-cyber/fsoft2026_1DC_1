//
// Created by masem on 11/06/2026.
//

#include "../headers/DepositoService.h"


DepositoService::DepositoService(DepositoRepository& r)
    : repo(r)
{}


DepositoOutDto DepositoService::adicionarDeposito(const DepositoInDto& dto)
{
    int id = repo.adicionar(dto.nome, dto.localizacao, dto.capacidadeMax);

    Deposito* d = repo.procurar(id);

    if (!d) return {};

    return DepositoMapper::toOutDto(*d);
}