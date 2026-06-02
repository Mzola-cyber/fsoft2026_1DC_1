//
// Created by Mário Figueira on 02/06/2026.
//

#ifndef GESTAOENCOMENDAS_CLIENTEVIEW_H
#define GESTAOENCOMENDAS_CLIENTEVIEW_H
#include "../../controller/Sistema.h"
#include"../../dtos/headers/DepositoOutDto.h"



class ClienteView {
    public:
        ClienteView();
    ClienteInDto getCliente();
    EncomendaInDto getEncomenda(const std::vector<DepositoOutDto>& depositos);
    int getIdEncomenda();
    int getIdCliente();
    void printCliente(const ClienteOutDto& cliente);
    void printEncomenda(const EncomendaOutDto& encomenda);
    void printEncomendas(const std::vector<EncomendaOutDto>& encomendas);

};


#endif //GESTAOENCOMENDAS_CLIENTEVIEW_H