//
// Created by Mário Figueira on 04/06/2026.
//

#ifndef GESTAOENCOMENDAS_DEPOSITOMAPPER_H
#define GESTAOENCOMENDAS_DEPOSITOMAPPER_H
#include"../../domain/headers/Deposito.h"
#include "../../dtos/headers/DepositoOutDto.h"

class DepositoMapper {
public:
    static DepositoOutDto toOutDto(const Deposito& deposito);
};


#endif //GESTAOENCOMENDAS_DEPOSITOMAPPER_H