#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include <vector>

#include "../domain/headers/Cliente.h"
#include "../domain/headers/Deposito.h"
#include "../domain/headers/Encomenda.h"
#include "../domain/headers/Veiculo.h"
#include "../repository/headers/DepositoRepository.h"
#include "../repository/headers/ClienteRepository.h"
#include "../repository/headers/VeiculoRepository.h"
#include "../repository/headers/EncomendaRepository.h"

class Sistema {
private:
    ClienteRepository      clientesRepository;
    DepositoRepository     depositosRepository;
    VeiculoRepository      veiculosRepository;
    EncomendaRepository    encomendaRepository;
    Cliente*   procurarCliente(int id);
    Deposito*  procurarDeposito(int id);
    Veiculo*   procurarVeiculo(int idVeiculo);
    Encomenda* procurarEncomenda(int id);

public:
    Sistema();
    int registarCliente(const std::string& nome, const std::string& contacto);
    bool removerCliente(int idCliente);
    int procurarClientePorIdOuContacto(const std::string& idOuContacto) const;

    int adicionarDeposito(const std::string& nome,
                          const std::string& localizacao,
                          int capacidadeMax);

    bool adicionarVeiculo(const std::string& matricula, double capacidadeMax);

    bool removerVeiculo(int idVeiculo);

    int criarEncomenda(int idCliente,
                       int idDepOrigem,
                       int idDepDestino,
                       const std::string& descricao,
                       double peso);

    bool avancarEstadoEncomenda(int idEncomenda);

    bool cancelarEncomenda(int idEncomenda);

    std::string consultarEstadoEncomenda(int idEncomenda, int idCliente) const;

    const std::vector<Cliente>&   getClientes()   const;
    const std::vector<Deposito>&  getDepositos()  const;
    const std::vector<Veiculo>&   getVeiculos()   const;
    const std::vector<Encomenda>& getEncomendas() const;
    std::string obterMatriculaVeiculo(int idVeiculo) const;
};

#endif
