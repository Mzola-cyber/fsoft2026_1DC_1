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
    double peso;
    EstadoEncomenda estado;

public:
    Encomenda(int id, int idCliente, int idDepOrigem, int idDepDestino, std::string descricao, double peso);
    int getId() const;
    int getIdCliente() const;
    // Compatibilidade: getPeso substitui getpeso; origem/destino suportam a listagem.
    double getPeso() const;
    double getpeso() const;
    int getIdVeiculo() const;
    EstadoEncomenda getEstado() const;
    std::string getDescricao() const;
    int getIdDepOrigem() const;
    int getIdDepDestino() const;
    void atribuirVeiculo(int idVeiculo);
    bool atualizarEstado(EstadoEncomenda novoestado);
};

#endif
