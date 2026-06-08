//
// Created by Mário Figueira on 02/06/2026.
//

#include "../headers/AdministradorView.h"
#include "../headers/UtilsView.h"
#include<vector>
#include <iostream>
#include <string>
using namespace std;

AdministradorView::AdministradorView() {

}
DepositoInDto AdministradorView::getDeposito() {
        UtilsView utils;

        DepositoInDto deposito;

        std::cout << "\n=== Adicionar Deposito ===\n";

        deposito.nome = utils.lerLinha("Nome do deposito: ");
        deposito.localizacao = utils.lerLinha("Localizacao: ");
        deposito.capacidadeMax = utils.lerInteiro("Capacidade maxima: ");

        return deposito;
    }

VeiculoInDto AdministradorView::getVeiculo() {

    UtilsView utils;
    VeiculoInDto veiculo;
    std::cout << "\n=== Adicionar Veiculo ===\n";

    veiculo.matricula = utils.lerLinha("Matricula: ");
    veiculo.capacidadeMax = utils.lerDouble("Capacidade maxima: ");
return veiculo;
}

int AdministradorView::getIdCliente() {
    UtilsView utils;
    return utils.lerInteiro("ID do cliente: ");

}

int AdministradorView::getIdVeiculo() {
    UtilsView utils;
    return utils.lerInteiro("ID do veiculo: ");

}

int AdministradorView::getIdEncomenda() {
    UtilsView utils;
    return utils.lerInteiro("ID da encomenda: ");

}

void AdministradorView::printDeposito(const DepositoOutDto& deposito) {
    std::cout << "\n===  Deposito ===\n";
    std::cout << "Nome: " << deposito.nome << "\n";
    std::cout << "Localizacao: " << deposito.localizacao << "\n";
    std::cout << "Capacidade: " << deposito.capacidadeMax << "\n";
    std::cout << "ID: " << deposito.id << "\n";


}

void AdministradorView::printVeiculo(const VeiculoOutDto& veiculo) {
    std::cout << "\n===  Veiculo ===\n";
    std::cout<<"Matricula: "<<veiculo.matricula<<"\n";
    std::cout<<"Capacidade: "<<veiculo.capacidadeMax<<"\n";
    std::cout<<"ID do veiculo: "<<veiculo.idVeiculo<<"\n";
    std::cout << "Disponibilidade: "
              << (veiculo.disponivel ? "Disponivel" : "Ocupado")
              << "\n";
}



void  AdministradorView::printClientes(const std::vector<ClienteOutDto>& clientes) {
    std::cout << "\n=== Clientes ===\n";

    if (clientes.empty()) {
        std::cout << "Sem clientes registados.\n";
        return;
    }

    for (const ClienteOutDto& cliente : clientes) {
        std::cout << "ID: " << cliente.id
                  << " | Nome: " << cliente.nome
                  << " | Contacto: " << cliente.contacto
                  << "\n";
    }
}

void AdministradorView::printDepositos(const std::vector<DepositoOutDto>& depositos) {

    std::cout << "\n=== Depositos ===\n";

    if (depositos.empty()) {
        std::cout << "Sem depositos registados.\n";
        return;
    }
    for (const DepositoOutDto& deposito : depositos) {
        std::cout << "ID: " << deposito.id
                  << " | Nome: " << deposito.nome
                  << " | Localizacao: " << deposito.localizacao
                  << " | Capacidade: " << deposito.capacidadeMax
                  << "\n";
    }

}

void AdministradorView::printVeiculos(const std::vector<VeiculoOutDto>& veiculos) {

    std::cout << "\n=== Veiculos ===\n";

    if (veiculos.empty()) {
        std::cout << "Sem veiculos registados.\n";
        return;
    }

    for (const VeiculoOutDto& veiculo : veiculos) {
        std::cout << "ID: " << veiculo.idVeiculo
                  << " | Matricula: " << veiculo.matricula
                  << " | Capacidade: " << veiculo.capacidadeMax
                  << " | "
                  << (veiculo.disponivel ? "Disponivel" : "Ocupado")
                  << "\n";
    }

}

void AdministradorView::printEncomendas(const std::vector<EncomendaOutDto>& encomendas) {
    UtilsView utils;

    std::cout << "\n=== Encomendas ===\n";

    if (encomendas.empty()) {
        std::cout << "Sem encomendas.\n";
        return;
    }

    for (const EncomendaOutDto& e : encomendas) {
        std::cout << "#" << e.id
                  << " | Cliente: " << e.idCliente
                  << " | " << e.idDepOrigem << " -> " << e.idDepDestino
                  << " | " << e.descricao
                  << " | Peso: " << e.peso<< " kg"
                  << " | Estado: " << utils.nomeEstado(e.estado)
                  << "\n";
    }
}