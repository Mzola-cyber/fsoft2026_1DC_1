//
// Created by masem on 11/06/2026.
//

#include "../headers/ClienteService.h"
ClienteService::ClienteService(ClienteRepository& c, EncomendaRepository& e)
    : clientesRepository(c), encomendaRepository(e) {}

bool ClienteService::removerCliente(int idCliente) {

    for (const auto& encomenda : encomendaRepository.getAll()) {
        if (encomenda.getIdCliente() == idCliente) {
            auto estado = encomenda.getEstado();
            if (estado != EstadoEncomenda::ENTREGUE &&
                estado != EstadoEncomenda::CANCELADA) {
                return false;
                }
        }
    }

    return clientesRepository.remover(idCliente);
}

ClienteOutDto ClienteService::registarCliente(const ClienteInDto& dto) {
    int id = clientesRepository.adicionar(dto.nome, dto.contacto);

    Cliente* cliente = clientesRepository.procurar(id);

    if (cliente == nullptr) {
        return ClienteOutDto{};
    }

    return ClienteMapper::toOutDto(*cliente);
}