//
// Created by Mário Figueira on 04/06/2026.
//

#ifndef GESTAOENCOMENDAS_CLIENTEMAPPER_H
#define GESTAOENCOMENDAS_CLIENTEMAPPER_H
#include "domain/headers/Cliente.h"
#include "dtos/headers/ClienteOutDto.h"

class ClienteMapper {
public:
    static ClienteOutDto toOutDto(const Cliente& cliente);
};


#endif //GESTAOENCOMENDAS_CLIENTEMAPPER_H