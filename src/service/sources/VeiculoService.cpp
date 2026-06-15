//
// Created by masem on 11/06/2026.
//

#include "../headers/VeiculoService.h"
#include <stdexcept>
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

    //VALIDAR DUPLICADOS (AQUI!)
    if (veiculosRepository.existePorMatricula(dto.matricula)) {
        throw std::invalid_argument("Matricula ja existe");
    }

    // CRIAR
    int id = veiculosRepository.adicionar(
        dto.matricula,
        dto.capacidadeMax
    );

    if (id == -1) {
        throw std::invalid_argument("Dados invalidos do veiculo");
    }

    Veiculo* veiculo = veiculosRepository.procurar(id);
    return VeiculoMapper::toOutDto(*veiculo);
}