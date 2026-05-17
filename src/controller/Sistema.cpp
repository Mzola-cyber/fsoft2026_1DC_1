#include "Sistema.h"

#include "service/Recomendacao.h"

Sistema::Sistema()
    : clientesRepository(),
      depositosRepository(),
      veiculosRepository(),
      encomendaRepository() {
}

Cliente* Sistema::procurarCliente(int id) {
    return clientesRepository.procurar(id);
}

Deposito* Sistema::procurarDeposito(int id) {





Sistema::Sistema()
    : clientesRepository(),
      depositosRepository(),
      veiculosRepository(),
      encomendaRepository() {
}



Cliente* Sistema::procurarCliente(int id) {
    return clientesRepository.procurar(id);
}

Deposito* Sistema::procurarDeposito(int id) {
    return depositosRepository.procurar(id);
}

Veiculo* Sistema::procurarVeiculo(int idVeiculo) {
    return veiculosRepository.procurar(idVeiculo);
}

Encomenda* Sistema::procurarEncomenda(int id) {
    return encomendaRepository.procurar(id);
}



int Sistema::registarCliente(const std::string& nome,
                             const std::string& contacto) {
    return clientesRepository.adicionar(nome, contacto);
}

bool Sistema::removerCliente(int idCliente) {
    for (const auto& encomenda : encomendaRepository.getAll()) {
        if (encomenda.getIdCliente() == idCliente) {
            EstadoEncomenda estado = encomenda.getEstado();
            if (estado != EstadoEncomenda::ENTREGUE && estado != EstadoEncomenda::CANCELADA) {
                return false;
            }
        }
    }

    return clientesRepository.remover(idCliente);
}

int Sistema::procurarClientePorIdOuContacto(const std::string& idOuContacto) const {
    try {
        int id = std::stoi(idOuContacto);
        if (clientesRepository.procurarConst(id) != nullptr) {
            return id;
        }
    } catch (...) {
        
    }
    
    
    for (const auto& c : clientesRepository.getAll()) {
        if (c.getContactoCliente() == idOuContacto) {
            return c.getId();
        }
    }
    
    return -1;
}



int Sistema::adicionarDeposito(const std::string& nome,
                               const std::string& localizacao,
                               int capacidadeMax) {
    return depositosRepository.adicionar(nome, localizacao, capacidadeMax);
}



bool Sistema::adicionarVeiculo(const std::string& matricula,
                               double capacidadeMax) {
    return veiculosRepository.adicionar(matricula, capacidadeMax) != -1;
}

bool Sistema::removerVeiculo(int idVeiculo) {
    for (const auto& encomenda : encomendaRepository.getAll()) {
        if (encomenda.getIdVeiculo() == idVeiculo) {
            EstadoEncomenda estado = encomenda.getEstado();
            if (estado == EstadoEncomenda::ATRIBUIDA ||
                estado == EstadoEncomenda::EM_TRANSPORTE) {
                return false;
            }
        }
    }

    return veiculosRepository.remover(idVeiculo);
}



int Sistema::criarEncomenda(int idCliente,
                            int idDepOrigem,
                            int idDepDestino,
                            const std::string& descricao,
                            double peso) {
    
    if (idDepOrigem == idDepDestino) return -1;
    if (peso <= 0.0)                  return -1;
    if (descricao.empty())            return -1;

    if (procurarCliente(idCliente)   == nullptr) return -1;
    if (procurarDeposito(idDepOrigem) == nullptr) return -1;
    if (procurarDeposito(idDepDestino) == nullptr) return -1;

    
    
    int id = encomendaRepository.adicionar(idCliente, idDepOrigem, idDepDestino,
                                          descricao, peso);
    if (id == -1) return -1;
    
    Encomenda* nova = encomendaRepository.procurar(id);
    if (nova == nullptr) return -1;

    
    int idVeiculo = Recomendacao::recomendarEReservar(veiculosRepository, peso);

    if (idVeiculo == -1) {
        
        
        nova->atualizarEstado(EstadoEncomenda::PENDENTE);
    } else {
        nova->atribuirVeiculo(idVeiculo);
        nova->atualizarEstado(EstadoEncomenda::ATRIBUIDA);
    }
    return id;
}

bool Sistema::avancarEstadoEncomenda(int idEncomenda) {
    Encomenda* e = procurarEncomenda(idEncomenda);
    if (e == nullptr) return false;

    
    
    
    
    switch (e->getEstado()) {
        case EstadoEncomenda::ATRIBUIDA:
            return e->atualizarEstado(EstadoEncomenda::EM_TRANSPORTE);

        case EstadoEncomenda::EM_TRANSPORTE: {
            bool ok = e->atualizarEstado(EstadoEncomenda::ENTREGUE);
            if (ok) {
                
                veiculosRepository.libertarVeiculo(e->getIdVeiculo());
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

    
    EstadoEncomenda atual = e->getEstado();
    if (atual == EstadoEncomenda::ENTREGUE ||
        atual == EstadoEncomenda::CANCELADA) {
        return false;
    }

    bool ok = e->atualizarEstado(EstadoEncomenda::CANCELADA);
    if (ok) {
        
        int idVeiculo = e->getIdVeiculo();
        if (idVeiculo != -1) {
            veiculosRepository.libertarVeiculo(idVeiculo);
        }
    }
    return ok;
}

std::string Sistema::obterMatriculaVeiculo(int idVeiculo) const {
    const Veiculo* v = veiculosRepository.procurarConst(idVeiculo);
    if (v != nullptr) return v->getMatriculaVeiculo();
    return {};
}



std::string Sistema::consultarEstadoEncomenda(int idEncomenda,
                                              int idCliente) const {
    const Encomenda* e = encomendaRepository.procurarConst(idEncomenda);
    if (e == nullptr) return "";

    
    if (e->getIdCliente() != idCliente) return "";

    std::string estado;
    switch (e->getEstado()) {
        case EstadoEncomenda::REGISTADA:     estado = "Registada"; break;
        case EstadoEncomenda::PENDENTE:      estado = "Pendente"; break;
        case EstadoEncomenda::ATRIBUIDA:     estado = "Atribuida"; break;
        case EstadoEncomenda::EM_TRANSPORTE: estado = "Em Transporte"; break;
        case EstadoEncomenda::ENTREGUE:      estado = "Entregue"; break;
        case EstadoEncomenda::CANCELADA:     estado = "Cancelada"; break;
    }
    return "Encomenda #" + std::to_string(e->getId()) +
           " - Estado: " + estado;
}

const std::vector<Cliente>&   Sistema::getClientes()   const { return clientesRepository.getAll(); }
const std::vector<Deposito>&  Sistema::getDepositos()  const { return depositosRepository.getAll(); }
const std::vector<Veiculo>&   Sistema::getVeiculos()   const { return veiculosRepository.getAll(); }
const std::vector<Encomenda>& Sistema::getEncomendas() const { return encomendaRepository.getAll(); }
