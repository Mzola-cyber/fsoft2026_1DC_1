#include "Sistema.h"

#include <iostream>
#include <ostream>

#include "../mappers/headers/ClienteMapper.h"
#include "../mappers/headers/DepositoMapper.h"
#include "../mappers/headers/VeiculoMapper.h"
#include "../mappers/headers/EncomendaMapper.h"
#include "../View/headers/ClienteView.h"
#include "../View/headers/AdministradorView.h"
#include "../View/headers/UtilsView.h"
#include "service/Recomendacao.h"

Sistema::Sistema()
    :clientesRepository(),
     depositosRepository(),
     veiculosRepository(),
     encomendaRepository()
{
}


void Sistema::runCliente() {
    ClienteView clienteView;
    UtilsView utils;
    bool sair = false;

    while (!sair) {
        std::cout << "\n--- Menu Cliente ---\n"

        << "1. Registar novo cliente\n"
        << "2. Criar encomenda\n"
        << "3. Consultar estado de encomenda\n"
        << "4. Cancelar encomenda\n"
        << "0. Voltar\n";
        int op = utils.lerInteiro("Opcao: ");

        switch (op) {
            case 1: {
                ClienteInDto dto=clienteView.getCliente();
                ClienteOutDto cliente=registarCliente(dto);
                if (cliente.id==0){
                    std::cout<<"não foi possivel registar o cliente.\n";
                } else {
                    clienteView.printCliente(cliente);
                }
                break;
            }
            case 2:{
                std::vector<DepositoOutDto> depositos = getDepositos();

                if (depositos.empty()) {
                    std::cout << "Nao existem depositos disponiveis.\n";
                    break;
                }

                EncomendaInDto dto = clienteView.getEncomenda(depositos);

                EncomendaOutDto encomenda = criarEncomenda(dto);

                if (encomenda.id == 0) {
                    std::cout << "Nao foi possivel criar encomenda.\n";
                } else {
                    clienteView.printEncomenda(encomenda);
                }

                break;
            }

            case 3: {
                int idCliente=clienteView.getIdCliente();
                int idEncomenda=clienteView.getIdEncomenda();
                std::string resultado=consultarEstadoEncomenda(idEncomenda,idCliente);
                if (resultado.empty()) {
                    std::cout<<"Encomenda nao encontrada ou nao pertence a este cliente.\n";
                } else {
                   std::cout<<resultado<<std::endl;
                }
                break;
            }

            case 4: {
                int idEncomenda=clienteView.getIdEncomenda();
                if (cancelarEncomenda(idEncomenda)) {
                    std::cout<<"Encomenda cancelada com sucesso.\n";

                }else{
                    std::cout<<"Não foi possivel cancelar a encomenda.\n";
                }
                break;
            }

            case 0:
                sair = true;
                break;
            default:
                std::cout << "Opcao invalida.\n";
        }
    }
}


void Sistema::runAdministrador() {
 UtilsView utils;
    AdministradorView adminView;

    bool sair = false;

    while (!sair) {
        std::cout << "\n===== MENU ADMINISTRADOR =====\n";
        std::cout << "1. Adicionar deposito\n";
        std::cout << "2. Adicionar veiculo\n";
        std::cout << "3. Remover veiculo\n";
        std::cout << "4. Remover cliente\n";
        std::cout << "5. Avancar estado de encomenda\n";
        std::cout << "6. Consultar informacao global\n";
        std::cout << "0. Voltar\n";

        int opcao = utils.lerInteiro("Opcao: ");

        switch (opcao) {
            case 1: {
                DepositoInDto dto = adminView.getDeposito();
                DepositoOutDto deposito = adicionarDeposito(dto);

                if (deposito.id == 0) {
                    std::cout << "Nao foi possivel adicionar deposito.\n";
                } else {
                    adminView.printDeposito(deposito);
                }

                break;
            }

            case 2: {
                VeiculoInDto dto = adminView.getVeiculo();
                VeiculoOutDto veiculo = adicionarVeiculo(dto);

                if (veiculo.idVeiculo == 0) {
                    std::cout << "Nao foi possivel adicionar veiculo.\n";
                } else {
                    adminView.printVeiculo(veiculo);
                }

                break;
            }

            case 3: {
                int idVeiculo = adminView.getIdVeiculo();

                if (removerVeiculo(idVeiculo)) {
                    std::cout << "Veiculo removido com sucesso.\n";
                } else {
                    std::cout << "Nao foi possivel remover o veiculo.\n";
                }

                break;
            }

            case 4: {
                int idCliente = adminView.getIdCliente();

                if (removerCliente(idCliente)) {
                    std::cout << "Cliente removido com sucesso.\n";
                } else {
                    std::cout << "Nao foi possivel remover o cliente.\n";
                }

                break;
            }

            case 5: {
                int idEncomenda = adminView.getIdEncomenda();

                if (avancarEstadoEncomenda(idEncomenda)) {
                    std::cout << "Estado da encomenda avancado com sucesso.\n";
                } else {
                    std::cout << "Nao foi possivel avancar o estado da encomenda.\n";
                }

                break;
            }

            case 6: {
                utils.imprimirSeparador();

                adminView.printClientes(getClientes());
                adminView.printDepositos(getDepositos());
                adminView.printVeiculos(getVeiculos());
                adminView.printEncomendas(getEncomendas());

                utils.imprimirSeparador();

                break;
            }

            case 0:
                sair = true;
                break;

            default:
                std::cout << "Opcao invalida.\n";
        }
    }
}

void Sistema::run() {
    UtilsView utils;
    std::cout << "================================================\n"
              << "  Sistema de Gestao de Encomendas\n"
              << "  FDS 2025/2026 - Grupo 01\n"
              << "================================================\n";

    bool sair = false;
    while (!sair) {
        std::cout << "\n--- Menu Principal ---\n"
                  << "1. Menu Cliente\n"
                  << "2. Menu Administrador\n"
                  << "0. Sair\n";
        int op = utils.lerInteiro("Opcao: ");
    switch (op) {
        case 1:
            runCliente();
            break;
        case 2:
            runAdministrador();
            break;
        case 0:
            sair = true;
            break;
        default:
            std::cout << "Opcao invalida!\n";
    }
    }
}

Cliente* Sistema::procurarCliente(int id) {
    return clientesRepository.procurar(id);
}

Deposito* Sistema::procurarDeposito(int id) {
    return depositosRepository.procurar(id);
}

Veiculo* Sistema::procurarVeiculo(int idVeiculo) {
    return veiculosRepository.procurar(idVeiculo);
}

Encomenda* Sistema::procurarEncomenda(int id) {
    return encomendaRepository.procurar(id);
}

ClienteOutDto Sistema::registarCliente(const ClienteInDto& dto) {
    int id = clientesRepository.adicionar(dto.nome, dto.contacto);

    Cliente* cliente = clientesRepository.procurar(id);

    if (cliente == nullptr) {
        return ClienteOutDto{};
    }

    return ClienteMapper::toOutDto(*cliente);
}


bool Sistema::removerCliente(int idCliente) {
    for (const auto& encomenda : encomendaRepository.getAll()) {
        if (encomenda.getIdCliente() == idCliente) {
            EstadoEncomenda estado = encomenda.getEstado();
            if (estado != EstadoEncomenda::ENTREGUE && estado != EstadoEncomenda::CANCELADA) {
                return false;
            }
        }
    }

    return clientesRepository.remover(idCliente);
}

int Sistema::procurarClientePorIdOuContacto(const std::string& idOuContacto) const {
    try {
        int id = std::stoi(idOuContacto);
        if (clientesRepository.procurarConst(id) != nullptr) {
            return id;
        }
    } catch (...) {
    }

    for (const auto& c : clientesRepository.getAll()) {
        if (c.getContactoCliente() == idOuContacto) {
            return c.getId();
        }
    }

    return -1;
}

DepositoOutDto Sistema::adicionarDeposito(const DepositoInDto& dto) {
    int id=depositosRepository.adicionar(dto.nome,dto.localizacao,dto.capacidadeMax);

    Deposito* deposito=depositosRepository.procurar(id);
    if (deposito==nullptr) {
        return DepositoOutDto{};
    }
    return DepositoMapper::toOutDto(*deposito);
}

VeiculoOutDto Sistema::adicionarVeiculo(const VeiculoInDto& dto) {

    int id=veiculosRepository.adicionar(dto.matricula,dto.capacidadeMax);
        Veiculo* veiculo=veiculosRepository.procurar(id);
        if (veiculo==nullptr) {
            return VeiculoOutDto{};
        }
        return VeiculoMapper::toOutDto(*veiculo);
}

bool Sistema::removerVeiculo(int idVeiculo) {
    for (const auto& encomenda : encomendaRepository.getAll()) {
        if (encomenda.getIdVeiculo() == idVeiculo) {
            EstadoEncomenda estado = encomenda.getEstado();
            if (estado == EstadoEncomenda::ATRIBUIDA ||
                estado == EstadoEncomenda::EM_TRANSPORTE) {
                return false;
            }
        }
    }

    return veiculosRepository.remover(idVeiculo);
}

EncomendaOutDto Sistema::criarEncomenda(const EncomendaInDto& dto) {
    if (dto.idDepOrigem == dto.idDepDestino) {
        return EncomendaOutDto{};
    }

    if (dto.peso <= 0 || dto.descricao.empty()) {
        return EncomendaOutDto{};
    }

    if (clientesRepository.procurar(dto.idCliente) == nullptr) {
        return EncomendaOutDto{};
    }

    if (depositosRepository.procurar(dto.idDepOrigem) == nullptr) {
        return EncomendaOutDto{};
    }

    if (depositosRepository.procurar(dto.idDepDestino) == nullptr) {
        return EncomendaOutDto{};
    }

    int id = encomendaRepository.adicionar(
        dto.idCliente,
        dto.idDepOrigem,
        dto.idDepDestino,
        dto.descricao,
        dto.peso
    );

    Encomenda* encomenda = encomendaRepository.procurar(id);

    if (encomenda == nullptr) {
        return EncomendaOutDto{};
    }

    return EncomendaMapper::toOutDto(*encomenda);
}

bool Sistema::avancarEstadoEncomenda(int idEncomenda) {
    Encomenda* e = procurarEncomenda(idEncomenda);
    if (e == nullptr) return false;

    switch (e->getEstado()) {
        case EstadoEncomenda::ATRIBUIDA:
            return e->atualizarEstado(EstadoEncomenda::EM_TRANSPORTE);
        case EstadoEncomenda::EM_TRANSPORTE: {
            bool ok = e->atualizarEstado(EstadoEncomenda::ENTREGUE);
            if (ok) {
                veiculosRepository.libertarVeiculo(e->getIdVeiculo());
            }
            return ok;
        }
        default:
            return false;
    }
}

bool Sistema::cancelarEncomenda(int idEncomenda) {
    Encomenda* e = procurarEncomenda(idEncomenda);
    if (e == nullptr) return false;

    EstadoEncomenda atual = e->getEstado();
    if (atual == EstadoEncomenda::ENTREGUE ||
        atual == EstadoEncomenda::CANCELADA) {
        return false;
    }

    bool ok = e->atualizarEstado(EstadoEncomenda::CANCELADA);
    if (ok) {
        int idVeiculo = e->getIdVeiculo();
        if (idVeiculo != -1) {
            veiculosRepository.libertarVeiculo(idVeiculo);
        }
    }
    return ok;
}

std::string Sistema::obterMatriculaVeiculo(int idVeiculo) const {
    const Veiculo* v = veiculosRepository.procurarConst(idVeiculo);
    if (v != nullptr) return v->getMatriculaVeiculo();
    return {};
}

std::string Sistema::consultarEstadoEncomenda(int idEncomenda,
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
 std::vector<ClienteOutDto> Sistema::getClientes() const {
    std::vector<ClienteOutDto> resultado;

    for (const auto& cliente : clientesRepository.getAll()) {
        resultado.push_back(
            ClienteMapper::toOutDto(cliente)
        );
    }

    return resultado;
}

 std::vector<DepositoOutDto>  Sistema::getDepositos()  const {
    std::vector<DepositoOutDto> resultado;

    for (const auto& deposito: depositosRepository.getAll()) {
        resultado.push_back(
            DepositoMapper::toOutDto(deposito)
        );
    }
    return resultado;
}

 std::vector<VeiculoOutDto>   Sistema::getVeiculos()   const {
        std::vector<VeiculoOutDto> resultado;

        for (const auto& veiculo: veiculosRepository.getAll()) {
            resultado.push_back(VeiculoMapper::toOutDto(veiculo));
        }
    return resultado;
    }

 std::vector<EncomendaOutDto> Sistema::getEncomendas() const {
    std::vector<EncomendaOutDto> resultado;
    for (const auto& encomenda: encomendaRepository.getAll()) {
        resultado.push_back(EncomendaMapper::toOutDto(encomenda));
    }
    return resultado;
}
