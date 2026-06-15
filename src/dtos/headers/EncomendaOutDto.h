//
// Created by Mário Figueira on 04/06/2026.
//

#ifndef GESTAOENCOMENDAS_ENCOMENDADTO_H
#define GESTAOENCOMENDAS_ENCOMENDADTO_H
#include<string>
#include "domain/headers/Encomenda.h"

class EncomendaOutDto {
    public:
    int id;
    int idCliente;
    int idVeiculo;
    int idDepOrigem;
    int idDepDestino;
    std::string descricao;
    double peso;
    EstadoEncomenda estado;

};


#endif //GESTAOENCOMENDAS_ENCOMENDADTO_H