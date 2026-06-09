//
// Created by Mário Figueira on 02/06/2026.
//

#include "../headers/ClienteView.h"
#include "../headers/UtilsView.h"
#include<vector>
#include<iostream>
#include <string>
using namespace std;


ClienteView::ClienteView() {
}

ClienteInDto ClienteView::getCliente() {
    UtilsView utils;
    ClienteInDto cliente;

    cout<<"\n##### REGISTAR CLIENTE ####\n#"<< endl;

    cliente.nome= utils.lerLinha("Nome:");
    cliente.contacto = utils.lerLinha("Contacto Telefonico: ");
return cliente;
}

EncomendaInDto ClienteView::getEncomenda(const std::vector<DepositoOutDto>& depositos) {
    UtilsView utils;

    EncomendaInDto encomenda;

    std::cout << "\n##### REGISTAR ENCOMENDA #####\n";

    encomenda.idCliente = utils.lerInteiro("ID do Cliente: ");

    if (depositos.empty()) {
        std::cout << "Nao existem depositos disponiveis.\n";
        return encomenda;
    }

    std::cout << "\n=== Depositos disponiveis ===\n";
    for (size_t i = 0; i < depositos.size(); ++i) {
        std::cout << "[" << i << "] "
                  << depositos[i].nome
                  << " | " << depositos[i].localizacao
                  << " | capacidade: " << depositos[i].capacidadeMax
                  << "\n";
    }

    int indiceOrigem = utils.lerInteiro("Escolha o indice do deposito de origem: ");

    if (indiceOrigem < 0 || indiceOrigem >= static_cast<int>(depositos.size())) {
        std::cout << "Indice de origem invalido.\n";
        return encomenda;
    }

    int indiceDestino = utils.lerInteiro("Escolha o indice do deposito de destino: ");

    if (indiceDestino < 0 || indiceDestino >= static_cast<int>(depositos.size())) {
        std::cout << "Indice de destino invalido.\n";
        return encomenda;
    }

    encomenda.idDepOrigem = depositos[indiceOrigem].id;
    encomenda.idDepDestino = depositos[indiceDestino].id;

    encomenda.descricao = utils.lerLinha("Descricao: ");
    encomenda.peso = utils.lerDouble("Peso (kg): ");

    return encomenda;
}


int ClienteView::getIdCliente() {
    UtilsView utils;

    return utils.lerInteiro("ID do Cliente: ");
}

int ClienteView::getIdEncomenda() {
    UtilsView utils;

    return utils.lerInteiro("ID da Encomenda: ");
}

void ClienteView::printCliente(const ClienteOutDto& cliente) {
    std::cout << "\n=== Cliente ===\n";
    std::cout << "ID: " << cliente.id << "\n";
    std::cout << "Nome: " << cliente.nome << "\n";
    std::cout << "Contacto: " << cliente.contacto << "\n";


}

void ClienteView::printEncomenda(const EncomendaOutDto& encomenda) {
    UtilsView utils;

    std::cout << "\n=== Encomenda ===\n";
    std::cout << "ID: " << encomenda.id << "\n";
    std::cout << "Cliente: " << encomenda.idCliente << "\n";
    std::cout << "Deposito origem: " << encomenda.idDepOrigem << "\n";
    std::cout << "Deposito destino: " << encomenda.idDepDestino << "\n";
    std::cout << "Descricao: " << encomenda.descricao << "\n";
    std::cout << "Peso: " << encomenda.peso << " kg\n";
    std::cout << "Estado: " << utils.nomeEstado(encomenda.estado) << "\n";

    if (encomenda.idVeiculo == -1) {
        std::cout << "Veiculo: sem veiculo atribuido\n";
    } else {
        std::cout << "ID Veiculo: " << encomenda.idVeiculo << "\n";
    }
}

void ClienteView::printEncomendas(const std::vector<EncomendaOutDto>& encomendas) {
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
                  << " | Peso: " << e.peso
                  << " kg"
                  << " | Estado: " << utils.nomeEstado(e.estado)
                  << "\n";
    }
}

