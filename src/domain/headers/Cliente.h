
#ifndef FSOFT_CLIENTE_H
#define FSOFT_CLIENTE_H

#include <string>

class Cliente {
private:
    int id;
    std::string nomeCliente;
    std::string contactoCliente;

public:
    Cliente(int id, std::string nomeCliente, std::string contactoCliente);
    int getId() const;
    std::string getNome() const;
    std::string getContactoCliente() const;
    void setNome(std::string nome);
};

#endif
