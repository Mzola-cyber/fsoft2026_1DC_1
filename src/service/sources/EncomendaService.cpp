//
// Created by masem on 11/06/2026.
//

#include "../headers/EncomendaService.h"
#include "mappers/headers/EncomendaMapper.h"
#include <iostream>

EncomendaService::EncomendaService(
    EncomendaRepository& encRepo,
    ClienteRepository& cliRepo,
    DepositoRepository& depRepo,
    VeiculoRepository& veiRepo
)
    : encomendaRepository(encRepo),
      clientesRepository(cliRepo),
      depositosRepository(depRepo),
      veiculosRepository(veiRepo),
      recomendacaoService(veiRepo)
{}

EncomendaOutDto EncomendaService::criarEncomenda(const EncomendaInDto& dto) {

    if (dto.idDepOrigem == dto.idDepDestino) return {};
    if (dto.peso <= 0 || dto.descricao.empty()) return {};

    Cliente* cliente = clientesRepository.procurar(dto.idCliente);
    Deposito* origem = depositosRepository.procurar(dto.idDepOrigem);
    Deposito* destino = depositosRepository.procurar(dto.idDepDestino);

    if (!cliente || !origem || !destino) return {};

    if (origem->getCapacidadeAtual() < dto.peso) return {};

    int id = encomendaRepository.adicionar(
        dto.idCliente,
        dto.idDepOrigem,
        dto.idDepDestino,
        dto.descricao,
        dto.peso
    );

    Encomenda* encomenda = encomendaRepository.procurar(id);
    if (!encomenda) return {};


    int idVeiculo = recomendacaoService.recomendarEReservar(dto.peso);

    if (idVeiculo != -1) {
        encomenda->atribuirVeiculo(idVeiculo);
        encomenda->atualizarEstado(EstadoEncomenda::ATRIBUIDA);
    } else {
        encomenda->atualizarEstado(EstadoEncomenda::PENDENTE);
    }

    //diminuir capacidade origem
    origem->diminuirCapacidade(dto.peso);
    return EncomendaMapper::toOutDto(*encomenda);
}

bool EncomendaService::avancarEstadoEncomenda(int idEncomenda) {
    Encomenda* e = encomendaRepository.procurar(idEncomenda);
    if (!e) return false;

    switch (e->getEstado()) {

        case EstadoEncomenda::ATRIBUIDA: {
            bool ok = e->atualizarEstado(EstadoEncomenda::EM_TRANSPORTE);

            if (ok) {
                //ocupação do depósito destino AQUI (correto)
                Deposito* destino = depositosRepository.procurar(e->getIdDepositoDestino());

                if (destino) {
                    destino->diminuirCapacidade(e->getPeso());
                }
            }

            return ok;
        }

        case EstadoEncomenda::EM_TRANSPORTE: {
            bool ok = e->atualizarEstado(EstadoEncomenda::ENTREGUE);

            if (ok) {
                veiculosRepository.libertarVeiculo(e->getIdVeiculo());

                //agora tenta atribuir pendentes
                tentarAtribuirPendentes();
            }

            return ok;
        }

        default:
            return false;
    }
}

bool EncomendaService::cancelarEncomenda(int idEncomenda) {

    Encomenda* e = encomendaRepository.procurar(idEncomenda);
    if (!e) return false;

    auto estado = e->getEstado();

    if (estado == EstadoEncomenda::ENTREGUE ||
        estado == EstadoEncomenda::CANCELADA) {
        return false;
        }

    bool ok = e->atualizarEstado(EstadoEncomenda::CANCELADA);
    if (ok) {
        //libertar veículo
        if (e->getIdVeiculo() != -1) {
            veiculosRepository.libertarVeiculo(e->getIdVeiculo());

            e->atribuirVeiculo(-1); // QUANDO CANCELADA, MUDA O IDVEICULO PARA -1 DA ENCOMENDA
        }
        tentarAtribuirPendentes();

        // devevolver capacidade ao deposito.
        Deposito* origem = depositosRepository.procurar(e->getIdDepositoOrigem());
        if (origem) {
            origem->aumentarCapacidade(e->getPeso());
        }
    }

    return ok;
}
std::string EncomendaService::consultarEstadoEncomenda(int idEncomenda,
                                              int idCliente) const {
    const Encomenda* e = encomendaRepository.procurarConst(idEncomenda);
    if (e == nullptr) return "";

    if (e->getIdCliente() != idCliente) return "";

    std::string estado;
    switch (e->getEstado()) {
        case EstadoEncomenda::REGISTADA:     estado = "Registada"; break;
        case EstadoEncomenda::PENDENTE:      estado = "Pendente"; break;
        case EstadoEncomenda::ATRIBUIDA:     estado = "Atribuida"; break;
        case EstadoEncomenda::EM_TRANSPORTE: estado = "Em Transporte"; break;
        case EstadoEncomenda::ENTREGUE:      estado = "Entregue"; break;
        case EstadoEncomenda::CANCELADA:     estado = "Cancelada"; break;
    }

    return "Encomenda #" + std::to_string(e->getId()) +
           " - Estado: " + estado;
}
void EncomendaService::tentarAtribuirPendentes() {

    for (auto& e : encomendaRepository.getAll()) {

        if (e.getEstado() != EstadoEncomenda::PENDENTE)
            continue;

        // 🔍 procurar veículo manualmente (estado real)
        for (auto& v : veiculosRepository.getAll()) {

            if (!v.estaDisponivel())
                continue;

            if (v.getCapacidade() >= e.getPeso()) {

                //reservar diretamente
                veiculosRepository.reservarVeiculo(v.getId());

                //atualizar encomenda
                e.atribuirVeiculo(v.getId());
                e.atualizarEstado(EstadoEncomenda::ATRIBUIDA);

                break; // passa à próxima encomenda
            }
        }
    }
}