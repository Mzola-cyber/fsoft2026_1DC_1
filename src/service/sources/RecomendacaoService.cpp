#include "../headers/RecomendacaoService.h"

#include <utility>
#include <algorithm>
#include <vector>
#include <limits>

RecomendacaoService::RecomendacaoService(VeiculoRepository& repo)
	: veiculosRepository(repo) {}

int RecomendacaoService::recomendarEReservar(double peso) {

	 const auto& veiculos = veiculosRepository.getAll();

	std::vector<std::pair<double, int>> candidatos;

	for (const auto& v : veiculos) {
		if (!v.estaDisponivel()) continue;

		double cap = v.getCapacidade();

		if (cap >= peso) {
			candidatos.emplace_back(cap, v.getId());
		}
	}

	std::sort(candidatos.begin(), candidatos.end());

	for (const auto& c : candidatos) {
		if (veiculosRepository.reservarVeiculo(c.second)) {
			return c.second;
		}
	}

	return -1;
}
