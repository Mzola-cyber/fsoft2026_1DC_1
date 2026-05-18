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
    [[nodiscard]] bool reservarVeiculo(int id);
    [[nodiscard]] bool libertarVeiculo(int id);
    bool remover(int id);
    Veiculo* procurar(int id);
    [[nodiscard]] const Veiculo* procurarConst(int id) const;
    [[nodiscard]] const std::vector<Veiculo>& getAll() const;
};

#endif


