//
// Created by masem on 14/06/2026.
//
#include <gtest/gtest.h>
#include "controller/Sistema.h"
#include "service/headers/DepositoService.h"

// CONSTRUTOR
TEST(DepositoServiceTest, DepositosExistem) {
    //ARRANGE
    Sistema sistema;
    //ACT
    auto deps = sistema.getDepositos();
    //ASSERT
    EXPECT_GT(deps.size(), 0);
}

// FUNÇÃO
TEST(DepositoServiceTest, CapacidadeAlterada) {
    //ARRANGE
    Sistema sistema;
    //ACT
    auto deps = sistema.getDepositos();
    int capacidadeAntes = deps[0].capacidadeMax;

    // simular mudança (ex: criar encomenda) -> AINDA NAO IMPLEMENTADO.  depois estudo mais
    //ASSERT
    EXPECT_GE(capacidadeAntes, 0); // VERIFICA QUE NAO EH NEGATIVA.
}