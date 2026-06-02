//
// Created by Mário Figueira on 02/06/2026.
//

#include "../headers/AdministradorView.h"
#include "../headers/UtilsView.h"

#include <iostream>
#include <string>
using namespace std;

AdministradorView::AdministradorView() {

}

void AdministradorView::menuAdministrador(Sistema &s) {
   UtilsView utils;
    bool sair = false;
    while (!sair) {
        std::cout << "\n--- Menu Administrador ---\n"
                  << "1. Adicionar deposito\n"
                  << "2. Adicionar veiculo\n"
                  << "3. Remover veiculo\n"
                  << "4. Remover cliente\n"
                  << "5. Avancar estado de encomenda\n"
                  << "6. Consultar informacao global\n"
                  << "0. Voltar\n";
        int op = utils.lerInteiro("Opcao: ");

        switch (op) {
            case 1: {
                std::string nome  = utils.lerLinha("Nome do deposito: ");
                std::string local = utils.lerLinha("Localizacao: ");
                int cap           = utils.lerInteiro("Capacidade maxima: ");
                int id = s.adicionarDeposito(nome, local, cap);
                if (id == -1) std::cout << "Dados invalidos.\n";
                else          std::cout << "Deposito #" << id << " adicionado.\n";
                break;
            }
            case 2: {
                std::string mat = utils.lerLinha("Matricula: ");
                double cap      = utils.lerDouble("Capacidade maxima (kg): ");
                if (s.adicionarVeiculo(mat, cap)) std::cout << "Veiculo adicionado.\n";
                else                              std::cout << "Falha (matricula duplicada ou capacidade invalida).\n";
                break;
            }
            case 3: {
                int id = utils.lerInteiro("ID do veiculo a remover: ");
                if (s.removerVeiculo(id)) std::cout << "Veiculo removido.\n";
                else                       std::cout << "Veiculo nao encontrado.\n";
                break;
            }
            case 4: {
                int id = utils.lerInteiro("ID do cliente: ");
                if (s.removerCliente(id)) std::cout << "Cliente removido.\n";
                else                      std::cout << "Cliente nao encontrado.\n";
                break;
            }
            case 5: {
                int id = utils.lerInteiro("ID da encomenda: ");
                if (s.avancarEstadoEncomenda(id)) std::cout << "Estado avancado.\n";
                else                              std::cout << "Transicao nao permitida ou encomenda inexistente.\n";
                break;
            }
            case 6:
                utils.imprimirSeparador();
                utils.listarClientes(s);
                utils.listarDepositos(s);
                utils.listarVeiculos(s);
                utils.listarEncomendas(s);
                utils.imprimirSeparador();
                break;
            case 0:
                sair = true;
                break;
            default:
                std::cout << "Opcao invalida.\n";
        }
    }
}


