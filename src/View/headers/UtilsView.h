//
// Created by Mário Figueira on 02/06/2026.
//

#ifndef GESTAOENCOMENDAS_UTILSVIEW_H
#define GESTAOENCOMENDAS_UTILSVIEW_H
#include "../../controller/Sistema.h"

class UtilsView {
public:
    UtilsView();
    void limparBuffer();
    int lerInteiro(const std::string& prompt);
    double lerDouble(const std::string& prompt);
    std::string lerLinha(const std::string& prompt);
    void imprimirSeparador();
    void listarClientes(const Sistema& s);
    void listarDepositos(const Sistema& s);
    void listarVeiculos(const Sistema& s);
    void listarEncomendas(const Sistema& s);
    void listarDepositosComIndices(const Sistema& s);
    const char* nomeEstado(EstadoEncomenda e);

};


#endif //GESTAOENCOMENDAS_UTILSVIEW_H