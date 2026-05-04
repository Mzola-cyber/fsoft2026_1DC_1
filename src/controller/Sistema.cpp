#include "Sistema.h"

#include "../service/Recomendacao.h"

// =============================================================
//  Sistema - Implementacao do controlador da aplicacao
// =============================================================
//
//  Cada metodo publico abaixo corresponde a um caso de uso ou a
//  uma operacao auxiliar identificada nas seccoes 6.2 e 4.1 do
//  relatorio tecnico. As decisoes de validacao aqui presentes
//  refletem as regras de negocio especificadas em cada caso de
//  uso (por exemplo, depositos distintos no UC1, matricula unica
//  no UC4, peso > 0).
// =============================================================

Sistema::Sistema()
    : proximoIdCliente(1),
      proximoIdDeposito(1),
      proximoIdEncomenda(1) {
}

// -------------------- Metodos auxiliares privados --------------------

Cliente* Sistema::procurarCliente(int id) {
    for (Cliente& c : clientes) {
        if (c.getId() == id) return &c;
    }
    return nullptr;
}

Deposito* Sistema::procurarDeposito(int id) {
    for (Deposito& d : depositos) {
        if (d.getId() == id) return &d;
    }
    return nullptr;
}

Veiculo* Sistema::procurarVeiculo(const std::string& matricula) {
    for (Veiculo& v : veiculos) {
        if (v.getMatricula() == matricula) return &v;
    }
    return nullptr;
}

Encomenda* Sistema::procurarEncomenda(int id) {
    for (Encomenda& e : encomendas) {
        if (e.getId() == id) return &e;
    }
    return nullptr;
}

// -------------------- Gestao de Clientes --------------------

int Sistema::registarCliente(const std::string& nome,
                             const std::string& contacto) {
    if (nome.empty() || contacto.empty()) {
        return -1;
    }
    int id = proximoIdCliente++;
    clientes.emplace_back(id, nome, contacto);
    return id;
}

bool Sistema::removerCliente(int idCliente) {
    for (auto it = clientes.begin(); it != clientes.end(); ++it) {
        if (it->getId() == idCliente) {
            clientes.erase(it);
            return true;
        }
    }
    return false;
}

// -------------------- Gestao de Depositos --------------------

int Sistema::adicionarDeposito(const std::string& nome,
                               const std::string& localizacao,
                               int capacidadeMax) {
    if (nome.empty() || localizacao.empty() || capacidadeMax <= 0) {
        return -1;
    }
    int id = proximoIdDeposito++;
    depositos.emplace_back(id, nome, localizacao, capacidadeMax);
    return id;
}

// -------------------- Gestao de Veiculos --------------------

bool Sistema::adicionarVeiculo(const std::string& matricula,
                               double capacidadeMax) {
    // UC4 - Regras de Negocio: matricula unica e capacidade > 0.
    if (matricula.empty() || capacidadeMax <= 0.0) {
        return false;
    }
    if (procurarVeiculo(matricula) != nullptr) {
        return false; // matricula duplicada
    }
    veiculos.emplace_back(matricula, capacidadeMax);
    return true;
}

bool Sistema::removerVeiculo(const std::string& matricula) {
    for (auto it = veiculos.begin(); it != veiculos.end(); ++it) {
        if (it->getMatricula() == matricula) {
            veiculos.erase(it);
            return true;
        }
    }
    return false;
}

// -------------------- Gestao de Encomendas (UC1) --------------------

int Sistema::criarEncomenda(int idCliente,
                            int idDepOrigem,
                            int idDepDestino,
                            const std::string& descricao,
                            double peso) {
    // Validacoes segundo as Regras de Negocio do UC1.
    if (idDepOrigem == idDepDestino) return -1;
    if (peso <= 0.0)                  return -1;
    if (descricao.empty())            return -1;

    if (procurarCliente(idCliente)   == nullptr) return -1;
    if (procurarDeposito(idDepOrigem) == nullptr) return -1;
    if (procurarDeposito(idDepDestino) == nullptr) return -1;

    // Cria a encomenda - entra no estado Registada (ver diagrama
    // de estados, seccao 8.3).
    int id = proximoIdEncomenda++;
    encomendas.emplace_back(id, idCliente, idDepOrigem, idDepDestino,
                            descricao, peso);
    Encomenda& nova = encomendas.back();

    // Tenta atribuir um veiculo automaticamente. Esta responsabilidade
    // e delegada ao servico Recomendacao (camada service).
    std::string matricula = Recomendacao::recomendarVeiculo(veiculos, peso);

    if (matricula.empty()) {
        // Fluxo alternativo 6a do UC1: nenhum veiculo disponivel,
        // a encomenda fica Pendente.
        nova.atualizarEstado(EstadoEncomenda::PENDENTE);
    } else {
        Veiculo* v = procurarVeiculo(matricula);
        if (v != nullptr) {
            v->setDisponivel(false);
            nova.atribuirVeiculo(matricula);
            nova.atualizarEstado(EstadoEncomenda::ATRIBUIDA);
        }
    }
    return id;
}

bool Sistema::avancarEstadoEncomenda(int idEncomenda) {
    Encomenda* e = procurarEncomenda(idEncomenda);
    if (e == nullptr) return false;

    // Transicoes validas segundo o diagrama de estados (seccao 8.3):
    //   ATRIBUIDA -> EM_TRANSPORTE -> ENTREGUE
    // A propria Encomenda::atualizarEstado deve rejeitar transicoes
    // invalidas (Protected Variations).
    switch (e->getEstado()) {
        case EstadoEncomenda::ATRIBUIDA:
            return e->atualizarEstado(EstadoEncomenda::EM_TRANSPORTE);

        case EstadoEncomenda::EM_TRANSPORTE: {
            bool ok = e->atualizarEstado(EstadoEncomenda::ENTREGUE);
            if (ok) {
                // Liberta o veiculo para futuras encomendas.
                Veiculo* v = procurarVeiculo(e->getMatriculaVeiculo());
                if (v != nullptr) v->setDisponivel(true);
            }
            return ok;
        }
        default:
            return false;
    }
}

bool Sistema::cancelarEncomenda(int idEncomenda) {
    Encomenda* e = procurarEncomenda(idEncomenda);
    if (e == nullptr) return false;

    // Nao se pode cancelar uma encomenda ja entregue ou cancelada.
    EstadoEncomenda atual = e->getEstado();
    if (atual == EstadoEncomenda::ENTREGUE ||
        atual == EstadoEncomenda::CANCELADA) {
        return false;
    }

    bool ok = e->atualizarEstado(EstadoEncomenda::CANCELADA);
    if (ok) {
        // Se um veiculo estava reservado, liberta-o.
        const std::string& matricula = e->getMatriculaVeiculo();
        if (!matricula.empty()) {
            Veiculo* v = procurarVeiculo(matricula);
            if (v != nullptr) v->setDisponivel(true);
        }
    }
    return ok;
}

// -------------------- Consultas (UC2 e UC3) --------------------

std::string Sistema::consultarEstadoEncomenda(int idEncomenda,
                                              int idCliente) const {
    // Procura non-const inline (nao podemos chamar procurarEncomenda
    // que e nao-const a partir de um metodo const).
    for (const Encomenda& e : encomendas) {
        if (e.getId() == idEncomenda) {
            // Regra de negocio do UC2: so consulta encomendas proprias.
            if (e.getIdCliente() != idCliente) return "";

            std::string estado;
            switch (e.getEstado()) {
                case EstadoEncomenda::REGISTADA:     estado = "Registada"; break;
                case EstadoEncomenda::PENDENTE:      estado = "Pendente"; break;
                case EstadoEncomenda::ATRIBUIDA:     estado = "Atribuida"; break;
                case EstadoEncomenda::EM_TRANSPORTE: estado = "Em Transporte"; break;
                case EstadoEncomenda::ENTREGUE:      estado = "Entregue"; break;
                case EstadoEncomenda::CANCELADA:     estado = "Cancelada"; break;
            }
            return "Encomenda #" + std::to_string(e.getId()) +
                   " - Estado: " + estado;
        }
    }
    return "";
}

const std::vector<Cliente>&   Sistema::getClientes()   const { return clientes; }
const std::vector<Deposito>&  Sistema::getDepositos()  const { return depositos; }
const std::vector<Veiculo>&   Sistema::getVeiculos()   const { return veiculos; }
const std::vector<Encomenda>& Sistema::getEncomendas() const { return encomendas; }