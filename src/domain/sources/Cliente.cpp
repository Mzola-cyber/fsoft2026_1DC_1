//
// Created by Mário Figueira on 02/05/2026.
//

#include "Cliente.h"
#include <stdexcept> //usada para usar o throw


Cliente::Cliente(int id,std::string nomeCliente, std::string contactoCliente ){

    if (nomeCliente.empty()) {
        throw std::invalid_argument("Nome invalido");
    }
    this->id = id;
    this->nomeCliente = nomeCliente;
    this->contactoCliente = contactoCliente;
}

int Cliente::getId() const {  //retorna o id do cliente
    return id;
}

std::string Cliente::getContactoCliente() const {
    return contactoCliente;
}
std::string Cliente::getNome() const {
    return nomeCliente;
}
void Cliente::setNome(std::string nome) {
    if (nome.empty()) {
        throw std::invalid_argument("Nome invalido"); //é para mandar nome invalido

    }
    this->nomeCliente = nome;


}