#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include <vector>
#include "domain/headers/Veiculo.h"
#include "repository/headers/VeiculoRepository.h"

class Recomendacao {
public:
	static int recomendarVeiculo(const std::vector<Veiculo>& veiculos, double peso);
	static int recomendarEReservar(VeiculoRepository& veiculosRepository, double peso);
};

#endif


