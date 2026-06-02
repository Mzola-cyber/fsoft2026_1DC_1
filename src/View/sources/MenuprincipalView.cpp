//
// Created by Mário Figueira on 02/06/2026.
//

#include "../headers/MenuprincipalView.h"

#include<iostream>
#include"../headers/UtilsView.h"
#include"../headers/ClienteView.h"
#include"../headers/AdministradorView.h"


using namespace std;


MenuprincipalView::MenuprincipalView() {

}

void MenuprincipalView::menuPrincipal(Sistema& sistema) {
    UtilsView utils;
    ClienteView cliente;
    AdministradorView admin;

    std::cout << "================================================\n"
              << "  Sistema de Gestao de Encomendas\n"
              << "  FDS 2025/2026 - Grupo 01\n"
              << "================================================\n";

    bool sair = false;
    while (!sair) {
        std::cout << "\n--- Menu Principal ---\n"
                  << "1. Entrar como Cliente\n"
                  << "2. Entrar como Administrador\n"
                  << "0. Sair\n";
        int op = utils.lerInteiro("Opcao: ");

        switch (op) {
            case 1: cliente.menuCliente(sistema); break;
            case 2: admin.menuAdministrador(sistema); break;
            case 0: sair = true; break;
            default: std::cout << "Opcao invalida.\n";
        }
    }
}
