#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include <vector>
#include "domain/headers/Veiculo.h"
#include "repository/headers/VeiculoRepository.h"

#pragma once

class RecomendacaoService {
private:
	VeiculoRepository& veiculosRepository;

public:
	RecomendacaoService(VeiculoRepository& repo);

	int recomendarEReservar(double peso);
};

#endif


