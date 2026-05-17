#include "repository/headers/DepositoRepository.h"
#include <algorithm>

DepositoRepository::DepositoRepository() {
    adicionar("Trindade", "Trindade", 5000);
    adicionar("Luanda", "Luanda", 8000);
    adicionar("Cazenga", "Cazenga", 6000);
    adicionar("Combatentes", "Combatentes", 7000);
    adicionar("Belas", "Belas", 4000);
    adicionar("Matosinhos", "Matosinhos", 3000);
}

int DepositoRepository::adicionar(const std::string& nome,
                                  const std::string& localizacao,
                                  int capacidadeMax) {
    if (nome.empty() || localizacao.empty() || capacidadeMax <= 0) return -1;
    int id = proximoId++;
    depositos.emplace_back(id, nome, localizacao, capacidadeMax);
    return id;
}

bool DepositoRepository::remover(int id) {
    auto it = std::remove_if(depositos.begin(), depositos.end(),
                             [&](const Deposito& d){ return d.getId() == id; });
    if (it != depositos.end()) {
        depositos.erase(it, depositos.end());
        return true;
    }
    return false;
}

Deposito* DepositoRepository::procurar(int id) {
    for (auto &d : depositos) if (d.getId() == id) return &d;
    return nullptr;
}

const Deposito* DepositoRepository::procurarConst(int id) const {
    for (const auto &d : depositos) if (d.getId() == id) return &d;
    return nullptr;
}

const std::vector<Deposito>& DepositoRepository::getAll() const {
    return depositos;
}

