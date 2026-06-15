#ifndef ENCOMENDAREPOSITORY_H
#define ENCOMENDAREPOSITORY_H

#include <vector>
#include <string>
#include "domain/headers/Encomenda.h"

class EncomendaRepository {
private:
    std::vector<Encomenda> encomendas;
    int proximoId = 1;

public:
    EncomendaRepository();

    int adicionar(int idCliente, int idDepOrigem, int idDepDestino,
                  const std::string &descricao, double peso);

    bool remover(int id);

    Encomenda *procurar(int id);

    const Encomenda *procurarConst(int id) const;

    //leitura
    const std::vector<Encomenda> &getAll() const;

    //modificação (ADICIONAR)
    std::vector<Encomenda> &getAll();

};

#endif


