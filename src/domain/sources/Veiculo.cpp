
#include "domain/headers/Veiculo.h"
#include <stdexcept>
#include<string>

Veiculo::Veiculo(int idVeiculo, std::string matricula, double capacidadeMax) {

    if (capacidadeMax<=0) {
        throw std::invalid_argument("capacidade do Veiculo invalido");
    }
    if (matricula.empty()) {
        throw std::invalid_argument("Matricula invalida");
    }

    this->idVeiculo = idVeiculo;
    this->matricula = matricula;
    this->capacidadeMax = capacidadeMax;
    this->disponivel = true;

}


int Veiculo::getId() const {
    return idVeiculo;
}
std::string Veiculo::getMatriculaVeiculo() const {
    return matricula;
}
double Veiculo::getCapacidade() const {
    return capacidadeMax;

}

bool Veiculo::estaDisponivel() const {
    return disponivel;

}
void Veiculo::setDisponivel(bool disponivel) {
    this->disponivel=disponivel;

}
