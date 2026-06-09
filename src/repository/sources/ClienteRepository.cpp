#include "repository/headers/ClienteRepository.h"
#include <algorithm>

ClienteRepository::ClienteRepository() {
    
}

int ClienteRepository::adicionar(const std::string& nome, const std::string& contacto) {
    if (nome.empty() || contacto.empty()) return -1;

    
    for (const auto& c : clientes) {
        if (c.getContactoCliente() == contacto) return -1;
    }

    int id = 1000 + proximoId++;
    clientes.emplace_back(id, nome, contacto);
    return id;
}

bool ClienteRepository::remover(int id) {
    auto it = std::remove_if(clientes.begin(), clientes.end(),
                             [&](const Cliente& c){ return c.getId() == id; });
    if (it != clientes.end()) {
        clientes.erase(it, clientes.end());
        return true;
    }
    return false;
}

Cliente* ClienteRepository::procurar(int id) {
    for (auto& c : clientes) {
        if (c.getId() == id) return &c;
    }
    return nullptr;
}

const Cliente* ClienteRepository::procurarConst(int id) const {
    for (const auto& c : clientes) {
        if (c.getId() == id) return &c;
    }
    return nullptr;
}

const std::vector<Cliente>& ClienteRepository::getAll() const {
    return clientes;
}
