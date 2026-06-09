//
// Created by Mário Figueira on 09/06/2026.
//

#ifndef GESTAOENCOMENDAS_MENUVIEW_H
#define GESTAOENCOMENDAS_MENUVIEW_H
#include <string>

class MenuView {
public:
    MenuView();
    int menuCliente();
    int menuAdministrador();
    int menuPrincipal();

    void printOpcaoInvalida();
    void printAplicacaoTerminada();
    void printMensagem(const std::string& mensagem);

};


#endif //GESTAOENCOMENDAS_MENUVIEW_H