//
// Created by Mário Figueira on 04/06/2026.
//

#ifndef GESTAOENCOMENDAS_DEPOSITODTO_H
#define GESTAOENCOMENDAS_DEPOSITODTO_H
#include <string>

class DepositoOutDto {
public:
    int id;
    std::string nome;
    std::string localizacao;
    int capacidadeMax;
};


#endif //GESTAOENCOMENDAS_DEPOSITODTO_H