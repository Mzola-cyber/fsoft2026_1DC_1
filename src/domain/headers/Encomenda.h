//
// Created by Mário Figueira on 03/05/2026.
//

#ifndef FSOFT_ENCOMENDA_H
#define FSOFT_ENCOMENDA_H
#include <string>

enum class EstadoEncomenda {
    REGISTADA,
    PENDENTE,
    ATRIBUIDA,
    EM_TRANSPORTE,
    ENTREGUE,
    CANCELADA
};

class Encomenda {
private:
    int id;
    int idCliente;
    int idVeiculo;
    int idDepOrigem;
    int idDepDestino;
    std::string descricao;
    float peso;
    EstadoEncomenda estado;


public:


    Encomenda(int id,int idCliente,int idDepOrigem, int idDepDestino,std::string descricao, double peso);
    int getId() const;
    int getIdCliente() const;
    double getpeso () const;
    int getIdveiculo () const;
    EstadoEncomenda getEstado() const;
    std::string getDescricao () const;

    void atribuirVeiculo(int idVeiculo);
    bool atualizarEstado(EstadoEncomenda novoestado);



};


#endif //FSOFT_ENCOMENDA