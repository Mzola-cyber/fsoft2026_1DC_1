//
// Created by masem on 11/06/2026.
//

#ifndef GESTAOENCOMENDAS_DEPOSITOSERVICE_H
#define GESTAOENCOMENDAS_DEPOSITOSERVICE_H
#include "repository/headers/DepositoRepository.h"
#include "dtos/headers/DepositoInDto.h"
#include "dtos/headers/DepositoOutDto.h"
#include "mappers/headers/DepositoMapper.h"

class DepositoService {
private:
    DepositoRepository& repo;

public:
    DepositoService(DepositoRepository& r);

    DepositoOutDto adicionarDeposito(const DepositoInDto& dto);
};



#endif //GESTAOENCOMENDAS_DEPOSITOSERVICE_H