//
// Created by masem on 14/06/2026.
//
#include <iostream>
#include "gtest/gtest.h"
#include "service/headers/ClienteService.h"
#include "controller/Sistema.h"

//CONSTRUTOR
TEST(ClienteServiceTest, RegistarCliente) {
    //Arrange
    Sistema sistema;
    //ACT
    ClienteInDto dto{"Zola", "912345678"};
    auto c = sistema.registarCliente(dto);

    //Assert
    EXPECT_NE(c.id, 0);
}

//FUNÇÃO
TEST(ClienteServiceTest, RemoverCliente) {
    //ARRANGE
    Sistema sistema;
    ClienteInDto dto{"Zola", "912345678"};

    //ACT
    auto c = sistema.registarCliente(dto);
    bool ok = sistema.removerCliente(c.id);

    //ASSERT
    EXPECT_TRUE(ok);
}

// VALIDAÇÃO
TEST(ClienteServiceTest, NaoRemoverClienteInexistente) {
    //ARRANGE
    Sistema sistema;

    //ACT
    bool ok = sistema.removerCliente(999);

    //ASSERT
    EXPECT_FALSE(ok);
}