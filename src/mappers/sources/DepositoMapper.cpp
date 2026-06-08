//
// Created by Mário Figueira on 04/06/2026.
//

#include "../headers/DepositoMapper.h"



DepositoOutDto DepositoMapper::toOutDto(const Deposito& deposito) {
    DepositoOutDto dto;
    dto.id = deposito.getId();
    dto.nome = deposito.getNome();
    dto.localizacao = deposito.getLocalizacao();
    dto.capacidadeMax = deposito.getCapacidadeMax();
return dto;
}

