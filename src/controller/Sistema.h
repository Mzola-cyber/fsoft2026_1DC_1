#ifndef SISTEMA_H
#define SISTEMA_H
//com a adicição das dtos no codigo, estou a fazer algumas alterações no sistema
#include <string>
#include <vector>

#include "domain/headers/Cliente.h"
#include "domain/headers/Deposito.h"
#include "domain/headers/Encomenda.h"
#include "domain/headers/Veiculo.h"
#include "repository/headers/DepositoRepository.h"
#include "repository/headers/ClienteRepository.h"
#include "repository/headers/VeiculoRepository.h"
#include "repository/headers/EncomendaRepository.h"
//adição dos headers das dtos

#include "../dtos/headers/ClienteInDto.h"
#include "../dtos/headers/ClienteOutDto.h"
#include "../dtos/headers/DepositoInDto.h"
#include "../dtos/headers/DepositoOutDto.h"
#include "../dtos/headers/VeiculoInDto.h"
#include "../dtos/headers/VeiculoOutDto.h"
#include "../dtos/headers/EncomendaInDto.h"
#include "../dtos/headers/EncomendaOutDto.h"

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
    void runCliente();
    void runAdministrador();

public:
    Sistema();
    void run();
    ClienteOutDto registarCliente(const ClienteInDto& dto);
    bool removerCliente(int idCliente);
    int procurarClientePorIdOuContacto(const std::string& idOuContacto) const;

    DepositoOutDto adicionarDeposito(const DepositoInDto& dto);

    VeiculoOutDto adicionarVeiculo(const VeiculoInDto& dto);

    bool removerVeiculo(int idVeiculo);

   EncomendaOutDto criarEncomenda(const EncomendaInDto& dto);

    bool avancarEstadoEncomenda(int idEncomenda);

    bool cancelarEncomenda(int idEncomenda);

    std::string consultarEstadoEncomenda(int idEncomenda, int idCliente) const;

     std::vector<ClienteOutDto>   getClientes()   const;
     std::vector<DepositoOutDto>  getDepositos()  const;
     std::vector<VeiculoOutDto>   getVeiculos()   const;
     std::vector<EncomendaOutDto> getEncomendas() const;
    std::string obterMatriculaVeiculo(int idVeiculo) const;
};

#endif
