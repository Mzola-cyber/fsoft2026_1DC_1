//
// Created by masem on 11/06/2026.
//

#include "../headers/VeiculoService.h"
VeiculoService::VeiculoService(VeiculoRepository& v, EncomendaRepository& e)
    : veiculosRepository(v), encomendaRepository(e) {}

bool VeiculoService::removerVeiculo(int idVeiculo) {

    for (const auto& encomenda : encomendaRepository.getAll()) {
        if (encomenda.getIdVeiculo() == idVeiculo) {
            auto estado = encomenda.getEstado();
            if (estado == EstadoEncomenda::ATRIBUIDA ||
                estado == EstadoEncomenda::EM_TRANSPORTE) {
                return false;
                }
        }
    }

    return veiculosRepository.remover(idVeiculo);
}

VeiculoOutDto VeiculoService::adicionarVeiculo(const VeiculoInDto& dto) {

    int id=veiculosRepository.adicionar(dto.matricula,dto.capacidadeMax);
    Veiculo* veiculo=veiculosRepository.procurar(id);
    if (veiculo==nullptr) {
        return VeiculoOutDto{};
    }
    return VeiculoMapper::toOutDto(*veiculo);
}