//
// Created by Mário Figueira on 04/06/2026.
//

#include "../headers/VeiculoMapper.h"


VeiculoOutDto VeiculoMapper::toOutDto(const Veiculo& veiculo) {
    VeiculoOutDto dto;
    dto.idVeiculo = veiculo.getId();
    dto.matricula= veiculo.getMatriculaVeiculo();
    dto.capacidadeMax= veiculo.getCapacidade();
    dto.disponivel=veiculo.estaDisponivel();
    return dto;
}
