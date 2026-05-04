#include <iostream>
#include <limits>
#include <string>

#include "controller/Sistema.h"

// =============================================================
//  main.cpp — Camada de Interface de Utilizador (UI)
// =============================================================
//
//  Esta e a unica parte do programa que comunica com o utilizador
//  atraves do terminal. Le opcoes, valida input e delega TODA a
//  logica de negocio na classe Sistema (controlador).
//
//  Esta separacao materializa, ao nivel do codigo, a estrutura
//  de pacotes apresentada na seccao 8.5 do relatorio:
//     ui (este ficheiro) -> controller (Sistema) -> domain
// =============================================================

// ----- Funcoes utilitarias de leitura segura do stdin -----

namespace {

void limparBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int lerInteiro(const std::string& prompt) {
    int valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            limparBuffer();
            return valor;
        }
        std::cout << "  Valor invalido. Tente novamente.\n";
        limparBuffer();
    }
}

double lerDouble(const std::string& prompt) {
    double valor;
    while (true) {
        std::cout << prompt;
        if (std::cin >> valor) {
            limparBuffer();
            return valor;
        }
        std::cout << "  Valor invalido. Tente novamente.\n";
        limparBuffer();
    }
}

std::string lerLinha(const std::string& prompt) {
    std::cout << prompt;
    std::string linha;
    std::getline(std::cin, linha);
    return linha;
}

void imprimirSeparador() {
    std::cout << "------------------------------------------------\n";
}

// ----- Apresentacao de listas (Consultar Informacao Global - UC3) -----

void listarClientes(const Sistema& s) {
    std::cout << "\n=== Clientes ===\n";
    const auto& clientes = s.getClientes();
    if (clientes.empty()) {
        std::cout << "  (sem clientes registados)\n";
        return;
    }
    for (const Cliente& c : clientes) {
        std::cout << "  ID " << c.getId()
                  << " | " << c.getNome()
                  << " | " << c.getContacto() << "\n";
    }
}

void listarDepositos(const Sistema& s) {
    std::cout << "\n=== Depositos ===\n";
    const auto& depositos = s.getDepositos();
    if (depositos.empty()) {
        std::cout << "  (sem depositos)\n";
        return;
    }
    for (const Deposito& d : depositos) {
        std::cout << "  ID " << d.getId()
                  << " | " << d.getNome()
                  << " | " << d.getLocalizacao()
                  << " | cap: " << d.getCapacidadeMax() << "\n";
    }
}

void listarVeiculos(const Sistema& s) {
    std::cout << "\n=== Veiculos ===\n";
    const auto& veiculos = s.getVeiculos();
    if (veiculos.empty()) {
        std::cout << "  (sem veiculos)\n";
        return;
    }
    for (const Veiculo& v : veiculos) {
        std::cout << "  " << v.getMatricula()
                  << " | cap: " << v.getCapacidadeMax()
                  << " | " << (v.estaDisponivel() ? "disponivel" : "ocupado")
                  << "\n";
    }
}

const char* nomeEstado(EstadoEncomenda e) {
    switch (e) {
        case EstadoEncomenda::REGISTADA:     return "Registada";
        case EstadoEncomenda::PENDENTE:      return "Pendente";
        case EstadoEncomenda::ATRIBUIDA:     return "Atribuida";
        case EstadoEncomenda::EM_TRANSPORTE: return "Em Transporte";
        case EstadoEncomenda::ENTREGUE:      return "Entregue";
        case EstadoEncomenda::CANCELADA:     return "Cancelada";
    }
    return "?";
}

void listarEncomendas(const Sistema& s) {
    std::cout << "\n=== Encomendas ===\n";
    const auto& encomendas = s.getEncomendas();
    if (encomendas.empty()) {
        std::cout << "  (sem encomendas)\n";
        return;
    }
    for (const Encomenda& e : encomendas) {
        std::cout << "  #" << e.getId()
                  << " | cliente " << e.getIdCliente()
                  << " | " << e.getIdDepOrigem() << " -> " << e.getIdDepDestino()
                  << " | peso " << e.getPeso()
                  << " | veiculo "
                  << (e.getMatriculaVeiculo().empty() ? "-" : e.getMatriculaVeiculo())
                  << " | " << nomeEstado(e.getEstado())
                  << "\n";
    }
}

// ----- Menu do Cliente -----

void menuCliente(Sistema& s) {
    bool sair = false;
    while (!sair) {
        std::cout << "\n--- Menu Cliente ---\n"
                  << "1. Registar novo cliente\n"
                  << "2. Criar encomenda\n"
                  << "3. Consultar estado de encomenda\n"
                  << "4. Cancelar encomenda\n"
                  << "0. Voltar\n";
        int op = lerInteiro("Opcao: ");

        switch (op) {
            case 1: {
                std::string nome     = lerLinha("Nome: ");
                std::string contacto = lerLinha("Contacto: ");
                int id = s.registarCliente(nome, contacto);
                if (id == -1) std::cout << "Dados invalidos.\n";
                else          std::cout << "Cliente registado com ID " << id << ".\n";
                break;
            }
            case 2: {
                int idCliente   = lerInteiro("ID do cliente: ");
                int idOrigem    = lerInteiro("ID do deposito de origem: ");
                int idDestino   = lerInteiro("ID do deposito de destino: ");
                std::string desc = lerLinha("Descricao: ");
                double peso     = lerDouble("Peso (kg): ");
                int id = s.criarEncomenda(idCliente, idOrigem, idDestino, desc, peso);
                if (id == -1) {
                    std::cout << "Nao foi possivel criar a encomenda. "
                                 "Verifique os dados (depositos distintos, peso > 0, ...).\n";
                } else {
                    std::cout << "Encomenda #" << id << " criada com sucesso.\n";
                }
                break;
            }
            case 3: {
                int idEnc      = lerInteiro("ID da encomenda: ");
                int idCliente  = lerInteiro("ID do cliente: ");
                std::string r  = s.consultarEstadoEncomenda(idEnc, idCliente);
                if (r.empty()) std::cout << "Encomenda nao encontrada ou nao pertence ao cliente.\n";
                else           std::cout << r << "\n";
                break;
            }
            case 4: {
                int idEnc = lerInteiro("ID da encomenda a cancelar: ");
                if (s.cancelarEncomenda(idEnc)) std::cout << "Encomenda cancelada.\n";
                else                            std::cout << "Nao foi possivel cancelar.\n";
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

// ----- Menu do Administrador -----

void menuAdministrador(Sistema& s) {
    bool sair = false;
    while (!sair) {
        std::cout << "\n--- Menu Administrador ---\n"
                  << "1. Adicionar deposito\n"
                  << "2. Adicionar veiculo\n"
                  << "3. Remover veiculo\n"
                  << "4. Remover cliente\n"
                  << "5. Avancar estado de encomenda\n"
                  << "6. Consultar informacao global\n"
                  << "0. Voltar\n";
        int op = lerInteiro("Opcao: ");

        switch (op) {
            case 1: {
                std::string nome  = lerLinha("Nome do deposito: ");
                std::string local = lerLinha("Localizacao: ");
                int cap           = lerInteiro("Capacidade maxima: ");
                int id = s.adicionarDeposito(nome, local, cap);
                if (id == -1) std::cout << "Dados invalidos.\n";
                else          std::cout << "Deposito #" << id << " adicionado.\n";
                break;
            }
            case 2: {
                std::string mat = lerLinha("Matricula: ");
                double cap      = lerDouble("Capacidade maxima (kg): ");
                if (s.adicionarVeiculo(mat, cap)) std::cout << "Veiculo adicionado.\n";
                else                              std::cout << "Falha (matricula duplicada ou capacidade invalida).\n";
                break;
            }
            case 3: {
                std::string mat = lerLinha("Matricula do veiculo a remover: ");
                if (s.removerVeiculo(mat)) std::cout << "Veiculo removido.\n";
                else                       std::cout << "Veiculo nao encontrado.\n";
                break;
            }
            case 4: {
                int id = lerInteiro("ID do cliente: ");
                if (s.removerCliente(id)) std::cout << "Cliente removido.\n";
                else                      std::cout << "Cliente nao encontrado.\n";
                break;
            }
            case 5: {
                int id = lerInteiro("ID da encomenda: ");
                if (s.avancarEstadoEncomenda(id)) std::cout << "Estado avancado.\n";
                else                              std::cout << "Transicao nao permitida ou encomenda inexistente.\n";
                break;
            }
            case 6:
                imprimirSeparador();
                listarClientes(s);
                listarDepositos(s);
                listarVeiculos(s);
                listarEncomendas(s);
                imprimirSeparador();
                break;
            case 0:
                sair = true;
                break;
            default:
                std::cout << "Opcao invalida.\n";
        }
    }
}

} // namespace

// ----- Ponto de entrada -----

int main() {
    Sistema sistema;

    std::cout << "================================================\n"
              << "  Sistema de Gestao de Encomendas\n"
              << "  FDS 2025/2026 - Grupo 01\n"
              << "================================================\n";

    bool sair = false;
    while (!sair) {
        std::cout << "\n--- Menu Principal ---\n"
                  << "1. Entrar como Cliente\n"
                  << "2. Entrar como Administrador\n"
                  << "0. Sair\n";
        int op = lerInteiro("Opcao: ");

        switch (op) {
            case 1: menuCliente(sistema); break;
            case 2: menuAdministrador(sistema); break;
            case 0: sair = true; break;
            default: std::cout << "Opcao invalida.\n";
        }
    }

    std::cout << "Adeus.\n";
    return 0;
}