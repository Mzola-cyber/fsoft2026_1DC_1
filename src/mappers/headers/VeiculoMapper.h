//
// Created by Mário Figueira on 04/06/2026.
//

#ifndef GESTAOENCOMENDAS_VEICULOMAPPER_H
#define GESTAOENCOMENDAS_VEICULOMAPPER_H
#include"../../domain/headers/Veiculo.h"
#include "dtos/headers/VeiculoOutDto.h"

class VeiculoMapper {
    public:
    static VeiculoOutDto toOutDto(const Veiculo& veiculo);
};


#endif //GESTAOENCOMENDAS_VEICULOMAPPER_H