//
// Created by Mário Figueira on 03/05/2026.
//

#ifndef FSOFT_DEPOSITO_H
#define FSOFT_DEPOSITO_H
#include <string>
#include <vector>


class Deposito {
private:
    int id;
    std::string nome;
    std::string localizacao;
    int capacidadeMax;

public:
    Deposito(int id,std::string nome, std::string localizacao, int capacidadeMax);
    int getId() const;
    std::string getNome() const;
    std::string getLocalizacao() const;
    int getCapacidadeMax() const;


};


#endif //FSOFT_DEPOSITO_H