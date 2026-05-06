//
// Created by Mário Figueira on 03/05/2026.
//

#include "Encomenda.h"
#include <stdexcept> //usada para usar o throw


Encomenda::Encomenda(int id, int idCliente, int idDepOrigem, int idDepDestino,std::string descricao,double peso) {

    if (peso <= 0) {
        throw std::invalid_argument("Peso invalido");
    }


    this->id = id;
    this->idCliente = idCliente;
    this->idDepOrigem = idDepOrigem;
    this->idDepDestino = idDepDestino;
    this->descricao = descricao;
    this->peso = peso;
    this->estado = EstadoEncomenda::REGISTADA;
    this->idVeiculo=-1;
}

int Encomenda:: getId() const {
    return id;
}
int Encomenda::getIdCliente() const {
    return idCliente;
}

int Encomenda::getIdveiculo() const {
    return idVeiculo;
}

double Encomenda::getpeso () const {
    return peso;
}
std::string Encomenda::getDescricao () const {
    return descricao;
}
EstadoEncomenda Encomenda::getEstado() const {
    return estado;
}
void Encomenda::atribuirVeiculo(int veiculo) {
    this->idVeiculo = idVeiculo;
}
bool Encomenda::atualizarEstado(EstadoEncomenda novoestado) { //a melhor opção seria de usar o enum só que no trabalho ta string

        if (estado == EstadoEncomenda::REGISTADA &&
            (novoestado == EstadoEncomenda::PENDENTE || novoestado == EstadoEncomenda::ATRIBUIDA)) {
            estado = novoestado;
            return true;
            }

        if (estado == EstadoEncomenda::ATRIBUIDA &&
            novoestado == EstadoEncomenda::EM_TRANSPORTE) {
            estado = novoestado;
            return true;
            }

        if (estado == EstadoEncomenda::EM_TRANSPORTE &&
            novoestado == EstadoEncomenda::ENTREGUE) {
            estado = novoestado;
            return true;
            }

        if (novoestado == EstadoEncomenda::CANCELADA &&
            estado != EstadoEncomenda::ENTREGUE &&
            estado != EstadoEncomenda::CANCELADA) {
            estado = novoestado;
            return true;
            }

        return false;
    }
