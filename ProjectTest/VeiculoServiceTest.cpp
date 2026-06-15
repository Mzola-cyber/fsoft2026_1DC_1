//
// Created by masem on 14/06/2026.
//
#include <gtest/gtest.h>
#include "controller/Sistema.h"
#include "service/headers/RecomendacaoService.h"

// CONSTRUTOR
TEST(VeiculoServiceTest, CriarVeiculo) {
    Sistema sistema;

    VeiculoInDto dto{"Candongueiro-003", 500};

    auto v = sistema.adicionarVeiculo(dto);

    EXPECT_NE(v.idVeiculo, 0);
}

// FUNÇÃO
TEST(VeiculoServiceTest, RemoverVeiculo) {
    Sistema sistema;

    VeiculoInDto dto{"CC-11-DD", 50};
    auto v = sistema.adicionarVeiculo(dto);

    bool ok = sistema.removerVeiculo(v.idVeiculo);

    EXPECT_TRUE(ok);
}

// REGRA (não remover em uso)
// Testa e resulta em false tentar tirar veiculo sendo usado.
TEST(VeiculoServiceTest, NaoRemoverVeiculoEmUso) {
        // ARRANGE
        Sistema sistema;

        VeiculoInDto dto{"EE-22-FF", 50};
        auto v = sistema.adicionarVeiculo(dto);

        ClienteInDto c{"Mario","912345678"};
        auto cliente = sistema.registarCliente(c);   // guardar retorno

        //usar ID correto
        EncomendaInDto e{cliente.id,1,2,"Produto",10};
        auto enc = sistema.criarEncomenda(e);

        // ACT
    bool ok = sistema.removerVeiculo(enc.idVeiculo);
    auto lista = sistema.getEncomendas();

        // ASSERT
        EXPECT_FALSE(ok);
}
