//
// Created by Mário Figueira on 03/05/2026.
//


#include "Deposito.h"
#include<stdexcept>

Deposito::Deposito(int id,std::string nome, std::string localizacao, int capacidadeMax) {

    if (nome.empty()) { //caso de dpositos vazios
        throw std::invalid_argument("Nome do deposito invalido");
    }

    if (localizacao.empty()) { //caso a localizacao esteja vazia
        throw std::invalid_argument("Localizacao do deposito invalida");
    }
    if (capacidadeMax <= 0) {
        throw std::invalid_argument("Capacidade invalida");
    }


    this->id = id;
    this->nome = nome;
    this->localizacao = localizacao;
    this->capacidadeMax = capacidadeMax;
}
int Deposito:: getId() const {
    return id;
}
std::string Deposito:: getNome() const {
    return nome;

}
std::string Deposito:: getLocalizacao() const {
    return localizacao;
}
int Deposito::getCapacidadeMax() const {
    return capacidadeMax;

}