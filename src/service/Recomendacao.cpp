#include "Recomendacao.h"

#include <algorithm>
#include <limits>
#include <utility>

int Recomendacao::recomendarVeiculo(const std::vector<Veiculo>& veiculos, double peso) {
	int bestId = -1;
	double bestCapacity = std::numeric_limits<double>::infinity();

	for (const Veiculo& v : veiculos) {
		if (!v.estaDisponivel()) continue;
		double cap = v.getCapacidade();
		if (cap >= peso && cap < bestCapacity) {
			bestCapacity = cap;
			bestId = v.getId();
		}
	}
	return bestId;
}

int Recomendacao::recomendarEReservar(VeiculoRepository& veiculosRepository, double peso) {
	const auto& veiculos = veiculosRepository.getAll();
	std::vector<std::pair<double, int>> candidatos;
	candidatos.reserve(veiculos.size());

	for (const Veiculo& v : veiculos) {
		if (!v.estaDisponivel()) continue;
		double cap = v.getCapacidade();
		if (cap >= peso) {
			candidatos.emplace_back(cap, v.getId());
		}
	}

	std::sort(candidatos.begin(), candidatos.end(),
	          [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
		          if (a.first != b.first) return a.first < b.first;
		          return a.second < b.second;
	          });

	for (const auto& candidato : candidatos) {
		if (veiculosRepository.reservarVeiculo(candidato.second)) {
			return candidato.second;
		}
	}

	return -1;
}

