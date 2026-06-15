//
// Created by Mário Figueira on 04/06/2026.
//

#ifndef GESTAOENCOMENDAS_ENCOMENDAINDTO_H
#define GESTAOENCOMENDAS_ENCOMENDAINDTO_H
class EncomendaInDto {
public:
    int idCliente;
    int idDepOrigem;
    int idDepDestino;
    int indiceDestino;
    int indiceOrigem;
    std::string nomeOrigem;
    std::string nomeDestino;
    std::string descricao;
    double peso;
};
#endif //GESTAOENCOMENDAS_ENCOMENDAINDTO_H