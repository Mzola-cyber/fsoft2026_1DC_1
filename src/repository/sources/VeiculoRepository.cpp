#include "repository/headers/VeiculoRepository.h"
#include <algorithm>

VeiculoRepository::VeiculoRepository() {
    
    
    adicionar("CANDONGEIRO-001", 1000.0);
    adicionar("CANDONGEIRO-002", 2000.0);
}

int VeiculoRepository::adicionar(const std::string& matricula, double capacidadeMax) {
    if (matricula.empty() || capacidadeMax <= 0) return -1;

    for (const auto& v : veiculos) {
        if (v.getMatriculaVeiculo() == matricula) {
            return -1;
        }
    }

    int id = proximoId++;
    veiculos.emplace_back(id, matricula, capacidadeMax);
    return id;
}

bool VeiculoRepository::reservarVeiculo(int id) {
    Veiculo* v = procurar(id);
    if (v == nullptr) return false;
    if (!v->estaDisponivel()) return false;
    v->setDisponivel(false);
    return true;
}

bool VeiculoRepository::libertarVeiculo(int id) {
    Veiculo* v = procurar(id);
    if (v == nullptr) return false;
    v->setDisponivel(true);
    return true;
}

bool VeiculoRepository::remover(int id) {
    auto it = std::remove_if(veiculos.begin(), veiculos.end(),
                             [&](const Veiculo& v){ return v.getId() == id; });
    if (it != veiculos.end()) {
        veiculos.erase(it, veiculos.end());
        return true;
    }
    return false;
}

Veiculo* VeiculoRepository::procurar(int id) {
    for (auto& v : veiculos) {
        if (v.getId() == id) return &v;
    }
    return nullptr;
}

const Veiculo* VeiculoRepository::procurarConst(int id) const {
    for (const auto& v : veiculos) {
        if (v.getId() == id) return &v;
    }
    return nullptr;
}

const std::vector<Veiculo>& VeiculoRepository::getAll() const {
    return veiculos;
}
