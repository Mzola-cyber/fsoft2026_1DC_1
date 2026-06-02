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

void ClienteView::menuCliente(Sistema& s) {
    UtilsView utils;
    bool sair = false;
    while (!sair) {
        std::cout << "\n--- Menu Cliente ---\n"

        << "1. Registar novo cliente\n"
        << "2. Criar encomenda\n"
        << "3. Consultar estado de encomenda\n"
        << "4. Cancelar encomenda\n"
        << "0. Voltar\n";
        int op = utils.lerInteiro("Opcao: ");

        switch (op) {
            case 1: {
                std::string nome =utils. lerLinha("Nome: ");
                std::string contacto =utils.lerLinha("Contacto Telefonico: ");
                int id = s.registarCliente(nome, contacto);
                if (id == -1) std::cout << "Dados invalidos ou contacto ja registado.\n";
                else          std::cout << "Cliente registado com sucesso.\n";
                break;
            }
            case 2: {

                std::string inputCliente = utils.lerLinha("Contacto do Cliente: ");
                int idCliente = s.procurarClientePorIdOuContacto(inputCliente);

                if (idCliente == -1) {
                    std::cout << "Cliente nao encontrado.\n";
                    break;
                }
                std::cout << "Cliente validado com sucesso. " << "\n";


                const auto& depositos = s.getDepositos();
                if (depositos.empty()) {
                    std::cout << "Nao existem depositos disponiveis.\n";
                    break;
                }

                std::cout << "\n=== Escolha o Deposito de ORIGEM ===\n";
                utils.listarDepositosComIndices(s);
                int indiceOrigem =utils.lerInteiro("Escolha o indice [0-" + std::to_string(depositos.size() - 1) + "]: ");
                if (indiceOrigem < 0 || indiceOrigem >= static_cast<int>(depositos.size())) {
                    std::cout << "Indice invalido.\n";
                    break;
                }
                int idOrigem = depositos[indiceOrigem].getId();


                int indiceDestino = -1;
                int idDestino = -1;
                while (true) {
                    std::cout << "\n=== Escolha o Deposito de DESTINO ===\n";
                    utils.listarDepositosComIndices(s);
                    indiceDestino = utils.lerInteiro("Escolha o indice [0-" + std::to_string(depositos.size() - 1) + "]: ");
                    if (indiceDestino < 0 || indiceDestino >= static_cast<int>(depositos.size())) {
                        std::cout << "Indice invalido. Tente novamente.\n";
                        continue;
                    }
                    idDestino = depositos[indiceDestino].getId();
                    if (idOrigem == idDestino) {
                        std::cout << "O deposito destino deve ser diferente do deposito origem. Por favor escolha novamente.\n";
                        continue;
                    }
                    break;
                }

                std::string desc =utils.lerLinha("Descricao: ");
                double peso     = utils.lerDouble("Peso (kg): ");
                int id = s.criarEncomenda(idCliente, idOrigem, idDestino, desc, peso);
                if (id == -1) {
                    std::cout << "Nao foi possivel criar a encomenda. "
                                 "Verifique os dados (depositos distintos, peso > 0, ...).\n";
                } else {
                    std::cout << "Encomenda #" << id << " criada com sucesso.\n";
                }
                break;
            }
            case 3: {


                std::string inputCliente = utils.lerLinha("Contacto do Cliente: ");
                int idCliente = s.procurarClientePorIdOuContacto(inputCliente);
                if (idCliente == -1) {
                    std::cout << "Cliente nao encontrado.\n";
                    break;
                }

                const auto& encomendas = s.getEncomendas();
                std::vector<int> clientIdx;
                for (size_t i = 0; i < encomendas.size(); ++i) {
                    if (encomendas[i].getIdCliente() == idCliente) clientIdx.push_back(static_cast<int>(i));
                }
                if (clientIdx.empty()) {
                    std::cout << "Sem encomendas para este cliente.\n";
                    break;
                }
                std::cout << "Encomendas do cliente:\n";
                for (size_t k = 0; k < clientIdx.size(); ++k) {
                    const auto& e = encomendas[clientIdx[k]];
                    std::cout << "  [" << k << "] " << e.getDescricao() << " | " << utils.nomeEstado(e.getEstado()) << "\n";
                }
                int escolha = utils.lerInteiro("Escolha o indice da encomenda para consultar: ");
                if (escolha < 0 || escolha >= static_cast<int>(clientIdx.size())) {
                    std::cout << "Indice invalido.\n";
                    break;
                }
                int idEnc = encomendas[clientIdx[escolha]].getId();
                std::string r  = s.consultarEstadoEncomenda(idEnc, idCliente);
                if (r.empty()) std::cout << "Encomenda nao encontrada ou nao pertence ao cliente.\n";
                else           std::cout << r << "\n";
                break;
            }
            case 4: {

                std::string inputCliente = utils.lerLinha("Contacto do Cliente: ");
                int idCliente = s.procurarClientePorIdOuContacto(inputCliente);
                if (idCliente == -1) {
                    std::cout << "Cliente nao encontrado.\n";
                    break;
                }

                const auto& encomendas = s.getEncomendas();
                std::vector<int> clientIdx;
                for (size_t i = 0; i < encomendas.size(); ++i) {
                    if (encomendas[i].getIdCliente() == idCliente) clientIdx.push_back(static_cast<int>(i));
                }
                if (clientIdx.empty()) {
                    std::cout << "Sem encomendas para este cliente.\n";
                    break;
                }
                std::cout << "Encomendas do cliente:\n";
                for (size_t k = 0; k < clientIdx.size(); ++k) {
                    const auto& e = encomendas[clientIdx[k]];
                    std::cout << "  [" << k << "] " << e.getDescricao() << " | " << utils.nomeEstado(e.getEstado()) << "\n";
                }
                int escolha = utils.lerInteiro("Escolha o indice da encomenda a cancelar: ");
                if (escolha < 0 || escolha >= static_cast<int>(clientIdx.size())) {
                    std::cout << "Indice invalido.\n";
                    break;
                }
                int idEnc = encomendas[clientIdx[escolha]].getId();
                if (s.cancelarEncomenda(idEnc)) std::cout << "Encomenda cancelada.\n";
                else                            std::cout << "Nao foi possivel cancelar ou encomenda nao existe.\n";
                break;
            }
            case 0:
                sair = true;
                break;
            default:
                std::cout << "Opcao invalida.\n";
        }
    }
}

