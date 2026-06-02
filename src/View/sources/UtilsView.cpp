//
// Created by Mário Figueira on 02/06/2026.
//

#include "../headers/UtilsView.h"
#include "../../controller/Sistema.h"
#include<iostream>
#include<limits>
#include<vector>
#include<string>

using namespace std;

UtilsView::UtilsView() {

}

void UtilsView::limparBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int UtilsView::lerInteiro(const std::string &prompt) {
    int valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            limparBuffer();
            return valor;
        }
        std::cout << "  Valor invalido. Tente novamente.\n";
        limparBuffer();
    }
}

double UtilsView::lerDouble(const std::string& prompt) {
    double valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            limparBuffer();
            return valor;
        }
        std::cout << "  Valor invalido. Tente novamente.\n";
        limparBuffer();
    }
}

std::string UtilsView::lerLinha(const std::string& prompt) {
    std::cout << prompt;
    std::string linha;
    std::getline(std::cin, linha);
    return linha;
}

void UtilsView::imprimirSeparador() {
    std::cout << "------------------------------------------------\n";
}


void UtilsView::listarClientes(const Sistema &s) {
    std::cout << "\n=== Clientes ===\n";
    const auto& clientes = s.getClientes();
    if (clientes.empty()) {
        std::cout << "  (sem clientes registados)\n";
        return;
    }
    for (const Cliente& c : clientes) {
        std::cout << "  ID " << c.getId()
                  << " | " << c.getNome()
                  << " | " << c.getContactoCliente() << "\n";
    }
}

void UtilsView::listarDepositos(const Sistema &s) {
    std::cout << "\n=== Depositos ===\n";
    const auto& depositos = s.getDepositos();
    if (depositos.empty()) {
        std::cout << "  (sem depositos)\n";
        return;
    }
    for (const Deposito& d : depositos) {
        std::cout << "  ID " << d.getId()
                  << " | " << d.getNome()
                  << " | " << d.getLocalizacao()
                  << " | cap: " << d.getCapacidadeMax() << "\n";
    }
}


void UtilsView::listarDepositosComIndices(const Sistema &s) {
    const auto& depositos = s.getDepositos();
    if (depositos.empty()) {
        std::cout << "  (sem depositos disponiveis)\n";
        return;
    }
    for (size_t i = 0; i < depositos.size(); ++i) {
        const auto& d = depositos[i];
        std::cout << "  [" << i << "] " << d.getNome()
                  << " (" << d.getLocalizacao() << ")"
                  << " | cap: " << d.getCapacidadeMax() << "\n";
    }
}


void UtilsView::listarVeiculos(const Sistema& s) {
    std::cout << "\n=== Veiculos ===\n";
    const auto& veiculos = s.getVeiculos();
    if (veiculos.empty()) {
        std::cout << "  (sem veiculos)\n";
        return;
    }
    for (const Veiculo& v : veiculos) {
        std::cout << "  " << v.getMatriculaVeiculo()
                  << " | cap: " << v.getCapacidade()
                  << " | " << (v.estaDisponivel() ? "disponivel" : "ocupado")
                  << "\n";
    }
}

const char* UtilsView::nomeEstado(EstadoEncomenda e) {
    switch (e) {
        case EstadoEncomenda::REGISTADA:
            return "Registada";
        case EstadoEncomenda::PENDENTE:
            return "Pendente";
        case EstadoEncomenda::ATRIBUIDA:
            return "Atribuida";
        case EstadoEncomenda::EM_TRANSPORTE:
            return "Em Transporte";
        case EstadoEncomenda::ENTREGUE:
            return "Entregue";
        case EstadoEncomenda::CANCELADA:
            return "Cancelada";
            }

            return "?";
        }



void UtilsView::listarEncomendas(const Sistema& s) {
    std::cout << "\n=== Encomendas ===\n";
    const auto& encomendas = s.getEncomendas();
    if (encomendas.empty()) {
        std::cout << "  (sem encomendas)\n";
        return;
    }
    for (const Encomenda& e : encomendas) {
        std::cout << "  #" << e.getId()
                  << " | cliente " << e.getIdCliente()
                  << " | " << e.getIdDepOrigem() << " -> " << e.getIdDepDestino()
                  << " | peso " << e.getPeso()
                   << " | veiculo "
                   << ([&s,&e]() {
                        int idV = e.getIdVeiculo();
                        if (idV == -1) return std::string("-");
                        std::string m = s.obterMatriculaVeiculo(idV);
                        return m.empty() ? std::string("-") : m;
                      })()
                  << " | " << nomeEstado(e.getEstado())
                  << "\n";
    }
}
