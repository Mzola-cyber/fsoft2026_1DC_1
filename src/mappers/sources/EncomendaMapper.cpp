//
// Created by Mário Figueira on 04/06/2026.
//

#include "../headers/EncomendaMapper.h"



EncomendaOutDto EncomendaMapper::toOutDto(const Encomenda &encomenda) {
    EncomendaOutDto dto;
     dto.id= encomenda.getId();
     dto.idCliente= encomenda.getIdCliente();
     dto.idVeiculo= encomenda.getIdVeiculo();
     dto.idDepOrigem= encomenda.getIdDepOrigem();
     dto.idDepDestino= encomenda.getIdDepDestino();
     dto.descricao= encomenda.getDescricao();
     dto.peso= encomenda.getPeso();
    dto.estado= encomenda.getEstado();

    return dto;

}
