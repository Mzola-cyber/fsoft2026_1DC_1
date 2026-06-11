



#include "domain/headers/Deposito.h"
#include<stdexcept>

Deposito::Deposito(int id,std::string nome, std::string localizacao, int capacidadeMax) {

    if (nome.empty()) { 
        throw std::invalid_argument("Nome do deposito invalido");
    }

    if (localizacao.empty()) { 
        throw std::invalid_argument("Localizacao do deposito invalida");
    }
    if (capacidadeMax <= 0) {
        throw std::invalid_argument("Capacidade invalida");
    }


    this->id = id;
    this->nome = nome;
    this->localizacao = localizacao;
    this->capacidadeMax = capacidadeMax;

    this->capacidadeAtual = capacidadeMax;
}
int Deposito::getId() const {
    return id;
}
std::string Deposito::getNome() const {
    return nome;

}
std::string Deposito::getLocalizacao() const {
    return localizacao;
}
int Deposito::getCapacidadeMax() const {
    return capacidadeMax;

}
double Deposito::getCapacidadeAtual() const {
    return capacidadeAtual;
}
void Deposito::diminuirCapacidade(double peso) {
    if (peso > 0 && capacidadeAtual >= peso) {
        capacidadeAtual -= peso;
    }
}
void Deposito::aumentarCapacidade(double peso) {
    if (peso > 0) {
        capacidadeAtual += peso;

        // ✅ evitar ultrapassar limite máximo
        if (capacidadeAtual > capacidadeMax) {
            capacidadeAtual = capacidadeMax;
        }
    }
}