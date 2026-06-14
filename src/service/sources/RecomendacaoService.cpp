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

	for (auto& v : veiculosRepository.getAll()) {

		std::cout << "Veiculo " << v.getId()
				  << " Disponivel=" << v.estaDisponivel()
				  << std::endl;

		if (!v.estaDisponivel()) continue;

		if (v.getCapacidade() >= peso) {

			if (veiculosRepository.reservarVeiculo(v.getId())) {
				return v.getId();
			}
		}
	}

	return -1;
}