//
// Created by masem on 14/06/2026.
//
#include <iostream>
#include "gtest/gtest.h"
#include "service/headers/EncomendaService.h"
#include "controller/Sistema.h"


// TESTE 1 → Criar válido
TEST(EncomendaServiceTest, CriarEncomendaValida) { //UC 1

    // Arrange
    Sistema sistema;

    EncomendaInDto dto{1001,1,2,"Produto",10};

    // Act
    auto result = sistema.criarEncomenda(dto);

    // Assert
    EXPECT_NE(result.id, !0);
}



// TESTE 2 → Criar inválido
TEST(EncomendaServiceTest, CriarEncomendaPesoInvalido) {

    Sistema sistema;

    EncomendaInDto dto{1001,1,2,"Produto",-5};

    auto result = sistema.criarEncomenda(dto);

    EXPECT_EQ(result.id, 0);
}



// TESTE 3 → Cancelar encomenda
TEST(EncomendaServiceTest, CancelarEncomendaValida) {

    Sistema sistema;

    ClienteInDto clienteDto{"zola", "912345678"};
    sistema.registarCliente(clienteDto);
    EncomendaInDto dto{1001,1,2,"Produto",10};
    auto e = sistema.criarEncomenda(dto);

    bool ok = sistema.cancelarEncomenda(e.id);

    EXPECT_TRUE(ok);
}



// TESTE 4 → Não cancelar entregue
TEST(EncomendaServiceTest, CancelarEncomendaJaEntregue) {

    Sistema sistema;

    EncomendaInDto dto{1001,1,2,"Produto",10};
    auto e = sistema.criarEncomenda(dto);

    sistema.avancarEstadoEncomenda(e.id); // ATRIBUIDA
    sistema.avancarEstadoEncomenda(e.id); // EM_TRANSPORTE
    sistema.avancarEstadoEncomenda(e.id); // ENTREGUE

    bool ok = sistema.cancelarEncomenda(e.id);

    EXPECT_FALSE(ok);
}



// TESTE 5 → Pendente -> Atribuida
TEST(EncomendaServiceTest, PendenteViraAtribuida) {

    Sistema sistema;
    for (int i = 9123; i < 9126; i++) {
        ClienteInDto clienteDto{"zola", std::to_string(i)};
        sistema.registarCliente(clienteDto);
    }

    EncomendaInDto dto1{1001,1,2,"A",10};
    EncomendaInDto dto2{1002,1,2,"B",10};
    EncomendaInDto dto3{1003,1,2,"C",10};

    auto e1 = sistema.criarEncomenda(dto1);
    auto e2 = sistema.criarEncomenda(dto2);
    auto e3 = sistema.criarEncomenda(dto3); // fica pendente

    // Act
    sistema.cancelarEncomenda(e2.id); // liberta veículo

    auto lista = sistema.getEncomendas();

    // Assert
    bool mudou = false;

    for (auto& e : lista) {
        if (e.id == e3.id &&
            e.estado == EstadoEncomenda::ATRIBUIDA) {
            mudou = true;
        }
    }

    EXPECT_TRUE(mudou);
}



// TESTE 6 → Veículo libertado
TEST(EncomendaServiceTest, VeiculoLibertadoAposCancelamento) {

    Sistema sistema;

    EncomendaInDto dto{1001,1,2,"Produto",10};
    auto e = sistema.criarEncomenda(dto);

    sistema.cancelarEncomenda(e.id);

    auto veiculos = sistema.getVeiculos();

    bool disponivel = false;

    for (auto& v : veiculos) {
        if (v.idVeiculo == 1 && v.disponivel) {
            disponivel = true;
        }
    }

    EXPECT_TRUE(disponivel);
}
