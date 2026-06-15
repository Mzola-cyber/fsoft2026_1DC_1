#include "../headers/RecomendacaoService.h"
#include <utility>
#include <algorithm>
#include <vector>
#include <limits>
#include <iostream>

RecomendacaoService::RecomendacaoService(VeiculoRepository& repo)
	: veiculosRepository(repo)
{}

int RecomendacaoService::recomendarEReservar(double peso) {

	for (const auto& v : veiculosRepository.getAll()) {

		// usar estado REAL do repository
		const Veiculo* real = veiculosRepository.procurarConst(v.getId());

		std::cout << "Veiculo " << v.getId()
				  << " Disponivel=" << real->estaDisponivel()
				  << std::endl;

		if (real->estaDisponivel() && real->getCapacidade() >= peso) {

			veiculosRepository.reservarVeiculo(v.getId());

			return v.getId();
		}
	}

	return -1;
}
