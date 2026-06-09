#ifndef VEICULOREPOSITORY_H
#define VEICULOREPOSITORY_H

#include <vector>
#include <string>
#include "domain/headers/Veiculo.h"

class VeiculoRepository {
private:
    std::vector<Veiculo> veiculos;
    int proximoId = 1;

public:
    VeiculoRepository();
    int adicionar(const std::string& matricula, double capacidadeMax);
     bool reservarVeiculo(int id);
     bool libertarVeiculo(int id);
    bool remover(int id);
    Veiculo* procurar(int id);
     const Veiculo* procurarConst(int id) const;
     const std::vector<Veiculo>& getAll() const;
};

#endif


