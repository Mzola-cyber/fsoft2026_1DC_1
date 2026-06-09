//
// Created by Mário Figueira on 09/06/2026.
//

#include "../headers/MenuView.h"
#include "../headers/UtilsView.h"
#include <iostream>

MenuView::MenuView() {

}

int MenuView::menuCliente() {

    UtilsView utils;
    std::cout << "\n==== Menu Cliente ====\n"

    << "1. Registar novo cliente\n"
    << "2. Criar encomenda\n"
    << "3. Consultar estado de encomenda\n"
    << "4. Cancelar encomenda\n"
    << "0. Voltar\n";

    return utils.lerInteiro("Opcao: ");
}

int MenuView::menuAdministrador() {

    UtilsView utils;
        std::cout << "\n===== Menu Administrador =====\n";
        std::cout << "1. Adicionar deposito\n";
        std::cout << "2. Adicionar veiculo\n";
        std::cout << "3. Remover veiculo\n";
        std::cout << "4. Remover cliente\n";
        std::cout << "5. Avancar estado de encomenda\n";
        std::cout << "6. Consultar informacao global\n";
        std::cout << "0. Voltar\n";

        return utils.lerInteiro("Opcao: ");

}

int MenuView::menuPrincipal() {
    UtilsView utils;

    std::cout << "\n===== SISTEMA DE GESTAO DE ENCOMENDAS =====\n";
    std::cout << "1. Menu Cliente\n";
    std::cout << "2. Menu Administrador\n";
    std::cout << "0. Sair\n";

    return utils.lerInteiro("Opcao: ");
}

void MenuView::printOpcaoInvalida() {
    std::cout << "Opcao invalida.\n";
}

void MenuView::printAplicacaoTerminada() {
    std::cout << "Aplicacao terminada.\n";
}

void MenuView::printMensagem(const std::string& mensagem) {
    std::cout << mensagem << "\n";
}