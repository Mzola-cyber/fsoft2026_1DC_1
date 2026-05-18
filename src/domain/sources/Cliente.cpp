



#include "domain/headers/Cliente.h"
#include <stdexcept> 


Cliente::Cliente(int id,std::string nomeCliente, std::string contactoCliente ){

    if (nomeCliente.empty()) {
        throw std::invalid_argument("Nome invalido");
    }
    this->id = id;
    this->nomeCliente = nomeCliente;
    this->contactoCliente = contactoCliente;
}

int Cliente::getId() const {  
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
        throw std::invalid_argument("Nome invalido"); 

    }
    this->nomeCliente = nome;

}