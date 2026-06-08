//
// Created by Mário Figueira on 04/06/2026.
//

#ifndef GESTAOENCOMENDAS_ENCOMENDAMAPPER_H
#define GESTAOENCOMENDAS_ENCOMENDAMAPPER_H
#include "../../domain/headers/Encomenda.h"
#include"dtos/headers/EncomendaOutDto.h"

class EncomendaMapper {
    public:
    static EncomendaOutDto toOutDto(const Encomenda& encomenda);
};


#endif //GESTAOENCOMENDAS_ENCOMENDAMAPPER_H