#ifndef CLIENTEREPOSITORY_H
#define CLIENTEREPOSITORY_H

#include <vector>
#include <string>
#include "domain/headers/Cliente.h"

class ClienteRepository {
private:
    std::vector<Cliente> clientes;
    int proximoId = 1;

public:
    ClienteRepository();
    int adicionar(const std::string& nome, const std::string& contacto);
    bool remover(int id);
    Cliente* procurar(int id);
    const Cliente* procurarConst(int id) const;
    const std::vector<Cliente>& getAll() const;
};

#endif
