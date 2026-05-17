#ifndef DEPOSITOREPOSITORY_H
#define DEPOSITOREPOSITORY_H

#include <vector>
#include <string>
#include "domain/headers/Deposito.h"

class DepositoRepository {
private:
    std::vector<Deposito> depositos;
    int proximoId = 1;

public:
    DepositoRepository();
    int adicionar(const std::string& nome, const std::string& localizacao, int capacidadeMax);
    bool remover(int id);
    Deposito* procurar(int id);
    const Deposito* procurarConst(int id) const;
    const std::vector<Deposito>& getAll() const;
};

#endif

