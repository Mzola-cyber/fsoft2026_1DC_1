//
// Created by masem on 14/06/2026.
//
#include <gtest/gtest.h>
#include "controller/Sistema.h"

//FLUXO COMPLETO
TEST(SistemaTest, CriarConsultar) {
    //ARRANGE
    Sistema sistema;
    ClienteInDto c{"Zola","912"};
    //ACT
    auto cliente = sistema.registarCliente(c);

    EncomendaInDto e{cliente.id,1,2,"Produto",10};
    auto enc = sistema.criarEncomenda(e);

    auto estado = sistema.consultarEstadoEncomenda(enc.id, cliente.id);
    //ASSERT
    EXPECT_FALSE(estado.empty());
}