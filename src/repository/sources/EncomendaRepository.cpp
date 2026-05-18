#include "repository/headers/EncomendaRepository.h"
#include <algorithm>

EncomendaRepository::EncomendaRepository() {
    
}

int EncomendaRepository::adicionar(int idCliente, int idDepOrigem, int idDepDestino,
                                   const std::string& descricao, double peso) {
    if (descricao.empty() || peso <= 0) return -1;
    
    int id = proximoId++;
    encomendas.emplace_back(id, idCliente, idDepOrigem, idDepDestino, descricao, peso);
    return id;
}

bool EncomendaRepository::remover(int id) {
    auto it = std::remove_if(encomendas.begin(), encomendas.end(),
                             [&](const Encomenda& e){ return e.getId() == id; });
    if (it != encomendas.end()) {
        encomendas.erase(it, encomendas.end());
        return true;
    }
    return false;
}

Encomenda* EncomendaRepository::procurar(int id) {
    for (auto& e : encomendas) {
        if (e.getId() == id) return &e;
    }
    return nullptr;
}

const Encomenda* EncomendaRepository::procurarConst(int id) const {
    for (const auto& e : encomendas) {
        if (e.getId() == id) return &e;
    }
    return nullptr;
}

const std::vector<Encomenda>& EncomendaRepository::getAll() const {
    return encomendas;
}
