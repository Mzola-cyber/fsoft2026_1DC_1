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
#include "../View/headers/MenuView.h"

Sistema::Sistema()
    : encomendaService(
        encomendaRepository,
        clientesRepository,
        depositosRepository,
        veiculosRepository
    ),clienteService(
        clientesRepository,
        encomendaRepository
    ), veiculoService(
        veiculosRepository,
        encomendaRepository
    ), depositoService(
        depositosRepository)
{}


void Sistema::runCliente() {

    MenuView menuView;
    ClienteView clienteView;
    bool sair = false;
    while (!sair) {
        int opcao = menuView.menuCliente();
        switch (opcao) {
            case 1: {
                ClienteInDto dto = clienteView.getCliente();
                ClienteOutDto cliente = registarCliente(dto);
                if (cliente.id == 0) {
                    menuView.printMensagem("Nao foi possivel registar cliente.");
                } else {
                    clienteView.printCliente(cliente);
                    menuView.printMensagem("Cliente Registrado com sucesso");
                }
                break;
            }
            case 2: {
                std::vector<DepositoOutDto> depositos = getDepositos();
                if (depositos.empty()) {
                    menuView.printMensagem("Nao existem depositos disponiveis.");
                    break;
                }

                EncomendaInDto dto = clienteView.getEncomenda(depositos);
                EncomendaOutDto encomenda = criarEncomenda(dto);
                if (encomenda.id == 0) {
                    menuView.printMensagem("Nao foi possivel criar encomenda.");
                } else {
                    clienteView.printEncomenda(encomenda);
                    menuView.printMensagem("Encomenda Registrada com sucesso");
                }
                break;
            }
            case 3: {
                int idCliente = clienteView.getIdCliente();
                int idEncomenda = clienteView.getIdEncomenda();
                std::string resultado = consultarEstadoEncomenda(idEncomenda, idCliente);
                if (resultado.empty()) {
                    menuView.printMensagem("Encomenda nao encontrada ou nao pertence ao cliente.");
                } else {
                    menuView.printMensagem(resultado);
                }
                break;
            }
            case 4: {
                menuView.printMensagem("### CANCELAR ENCOMENDA ###");
                int idCliente = clienteView.getIdCliente();
                ClienteInDto c = clienteView.getContacto();
                int idEncomenda = clienteView.getIdEncomenda();
                if (!verificarCliente(idCliente, c.contacto)) {
                    menuView.printMensagem("Cliente ou contacto invalido.");
                    break;
                }

                if (!verificarEncomendaCliente(idEncomenda, idCliente)) {
                    menuView.printMensagem("Encomenda nao pertence ao cliente.");
                    break;
                }

                if (cancelarEncomenda(idEncomenda)) {
                    menuView.printMensagem("Encomenda cancelada com sucesso.");
                } else {
                    menuView.printMensagem("Nao foi possivel cancelar a encomenda.");
                }
                break;
            }
            case 0:
                sair = true;
                break;
            default:
                menuView.printOpcaoInvalida();
                break;
        }
    }
}

void Sistema::runAdministrador() {
    MenuView menuView;
    AdministradorView adminView;
    UtilsView utilsView;
    bool sair = false;
    while (!sair) {
        int opcao = menuView.menuAdministrador();
        switch (opcao) {
            case 1: {
                DepositoInDto dto = adminView.getDeposito();
                DepositoOutDto deposito = adicionarDeposito(dto);
                if (deposito.id == 0) {
                    menuView.printMensagem("Nao foi possivel adicionar deposito.");
                } else {
                    adminView.printDeposito(deposito);
                    menuView.printMensagem("Deposito Adicionado com sucesso");
                }
                break;
            }
            case 2: {

                VeiculoInDto dto = adminView.getVeiculo();

                try {
                    VeiculoOutDto veiculo = adicionarVeiculo(dto);

                    adminView.printVeiculo(veiculo);
                    menuView.printMensagem("Veiculo Adicionado com sucesso");
                } catch (std::invalid_argument& e) {

                    menuView.printMensagem(e.what());
                }

                break;
            }
            case 3: {
                int idVeiculo = adminView.getIdVeiculo();
                if (removerVeiculo(idVeiculo)) {
                    menuView.printMensagem("Veiculo removido com sucesso.");
                } else {
                    menuView.printMensagem("Nao foi possivel remover o veiculo.");
                }
                break;
            }
            case 4: {
                int idCliente = adminView.getIdCliente();
                if (removerCliente(idCliente)) {
                    menuView.printMensagem("Cliente removido com sucesso.");
                } else {
                    menuView.printMensagem("Nao foi possivel remover o cliente.");
                }
                break;
            }
            case 5: {
                int idEncomenda = adminView.getIdEncomenda();
                if (avancarEstadoEncomenda(idEncomenda)) {
                    menuView.printMensagem("Estado da encomenda avancado com sucesso.");
                } else {
                    menuView.printMensagem("Nao foi possivel avancar o estado da encomenda.");
                }
                break;
            }
            case 6: {
                utilsView.imprimirSeparador();
                adminView.printClientes(getClientes());
                adminView.printDepositos(getDepositos());
                adminView.printVeiculos(getVeiculos());
                adminView.printEncomendas(getEncomendas());
                utilsView.imprimirSeparador();
                break;
            }
            case 0:
                sair = true;
                break;
            default:
                menuView.printOpcaoInvalida();
                break;
        }
    }
}

void Sistema::run() {
   MenuView menuview;
    bool sair = false;
    while (!sair) {
        int op = menuview.menuPrincipal();
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
            menuview.printOpcaoInvalida();
    }
    }
}


ClienteOutDto Sistema::registarCliente(const ClienteInDto& dto) {
    return clienteService.registarCliente(dto);
}


bool Sistema::removerCliente(int idCliente) {
  return clienteService.removerCliente(idCliente);
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
    return depositoService.adicionarDeposito(dto);
}

VeiculoOutDto Sistema::adicionarVeiculo(const VeiculoInDto& dto) {
    return veiculoService.adicionarVeiculo(dto);
}

bool Sistema::removerVeiculo(int idVeiculo) {
    return veiculoService.removerVeiculo(idVeiculo);
}

EncomendaOutDto Sistema::criarEncomenda(const EncomendaInDto& dto) {
    return encomendaService.criarEncomenda(dto);
}

bool Sistema::avancarEstadoEncomenda(int idEncomenda) {
    return encomendaService.avancarEstadoEncomenda(idEncomenda);
}

bool Sistema::cancelarEncomenda(int idEncomenda) {
    return encomendaService.cancelarEncomenda(idEncomenda);
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

std::string Sistema::obterMatriculaVeiculo(int idVeiculo) const {
    const Veiculo* v = veiculosRepository.procurarConst(idVeiculo);
    if (v != nullptr) return v->getMatriculaVeiculo();
    return {};
}

std::string Sistema::consultarEstadoEncomenda(int idEncomenda,
                                              int idCliente) const {
    return encomendaService.consultarEstadoEncomenda(idEncomenda, idCliente);
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
bool Sistema::verificarCliente(int idCliente, const std::string& contacto) {
    Cliente* c = clientesRepository.procurar(idCliente);

    if (!c) return false;

    return c->getContactoCliente() == contacto;
}
bool Sistema::verificarEncomendaCliente(int idEncomenda, int idCliente) {
    Encomenda* e = encomendaRepository.procurar(idEncomenda);

    if (!e) return false;

    return e->getIdCliente() == idCliente;
}
