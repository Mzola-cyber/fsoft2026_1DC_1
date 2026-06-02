//
// Created by Mário Figueira on 04/06/2026.
//

#include "../headers/ClienteMapper.h"


ClienteOutDto ClienteMapper::toOutDto(const Cliente& cliente) {
    ClienteOutDto dto;

    dto.id = cliente.getId();
    dto.nome = cliente.getNome();
    dto.contacto = cliente.getContactoCliente();

    return dto;
}