#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "controller/Sistema.h"

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
                  << " | " << c.getContactoCliente() << "\n";
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
        std::cout << "  " << v.getMatriculaVeiculo()
                  << " | cap: " << v.getCapacidade()
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
                   << ([&s,&e]() {
                        int idV = e.getIdVeiculo();
                        if (idV == -1) return std::string("-");
                        std::string m = s.obterMatriculaVeiculo(idV);
                        return m.empty() ? std::string("-") : m;
                      })()
                  << " | " << nomeEstado(e.getEstado())
                  << "\n";
    }
}


void listarDepositosComIndices(const Sistema& s) {
    const auto& depositos = s.getDepositos();
    if (depositos.empty()) {
        std::cout << "  (sem depositos disponiveis)\n";
        return;
    }
    for (size_t i = 0; i < depositos.size(); ++i) {
        const auto& d = depositos[i];
        std::cout << "  [" << i << "] " << d.getNome()
                  << " (" << d.getLocalizacao() << ")"
                  << " | cap: " << d.getCapacidadeMax() << "\n";
    }
}





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
                std::string contacto = lerLinha("Contacto Telefonico: ");
                int id = s.registarCliente(nome, contacto);
                if (id == -1) std::cout << "Dados invalidos ou contacto ja registado.\n";
                else          std::cout << "Cliente registado com sucesso.\n";
                break;
            }
            case 2: {

                std::string inputCliente = lerLinha("Contacto do Cliente: ");
                int idCliente = s.procurarClientePorIdOuContacto(inputCliente);

                if (idCliente == -1) {
                    std::cout << "Cliente nao encontrado.\n";
                    break;
                }
                std::cout << "Cliente validado com sucesso. " << "\n";


                const auto& depositos = s.getDepositos();
                if (depositos.empty()) {
                    std::cout << "Nao existem depositos disponiveis.\n";
                    break;
                }

                std::cout << "\n=== Escolha o Deposito de ORIGEM ===\n";
                listarDepositosComIndices(s);
                int indiceOrigem = lerInteiro("Escolha o indice [0-" + std::to_string(depositos.size() - 1) + "]: ");
                if (indiceOrigem < 0 || indiceOrigem >= static_cast<int>(depositos.size())) {
                    std::cout << "Indice invalido.\n";
                    break;
                }
                int idOrigem = depositos[indiceOrigem].getId();


                int indiceDestino = -1;
                int idDestino = -1;
                while (true) {
                    std::cout << "\n=== Escolha o Deposito de DESTINO ===\n";
                    listarDepositosComIndices(s);
                    indiceDestino = lerInteiro("Escolha o indice [0-" + std::to_string(depositos.size() - 1) + "]: ");
                    if (indiceDestino < 0 || indiceDestino >= static_cast<int>(depositos.size())) {
                        std::cout << "Indice invalido. Tente novamente.\n";
                        continue;
                    }
                    idDestino = depositos[indiceDestino].getId();
                    if (idOrigem == idDestino) {
                        std::cout << "O deposito destino deve ser diferente do deposito origem. Por favor escolha novamente.\n";
                        continue;
                    }
                    break;
                }

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


                std::string inputCliente = lerLinha("Contacto do Cliente: ");
                int idCliente = s.procurarClientePorIdOuContacto(inputCliente);
                if (idCliente == -1) {
                    std::cout << "Cliente nao encontrado.\n";
                    break;
                }

                const auto& encomendas = s.getEncomendas();
                std::vector<int> clientIdx;
                for (size_t i = 0; i < encomendas.size(); ++i) {
                    if (encomendas[i].getIdCliente() == idCliente) clientIdx.push_back(static_cast<int>(i));
                }
                if (clientIdx.empty()) {
                    std::cout << "Sem encomendas para este cliente.\n";
                    break;
                }
                std::cout << "Encomendas do cliente:\n";
                for (size_t k = 0; k < clientIdx.size(); ++k) {
                    const auto& e = encomendas[clientIdx[k]];
                    std::cout << "  [" << k << "] " << e.getDescricao() << " | " << nomeEstado(e.getEstado()) << "\n";
                }
                int escolha = lerInteiro("Escolha o indice da encomenda para consultar: ");
                if (escolha < 0 || escolha >= static_cast<int>(clientIdx.size())) {
                    std::cout << "Indice invalido.\n";
                    break;
                }
                int idEnc = encomendas[clientIdx[escolha]].getId();
                std::string r  = s.consultarEstadoEncomenda(idEnc, idCliente);
                if (r.empty()) std::cout << "Encomenda nao encontrada ou nao pertence ao cliente.\n";
                else           std::cout << r << "\n";
                break;
            }
            case 4: {

                std::string inputCliente = lerLinha("Contacto do Cliente: ");
                int idCliente = s.procurarClientePorIdOuContacto(inputCliente);
                if (idCliente == -1) {
                    std::cout << "Cliente nao encontrado.\n";
                    break;
                }

                const auto& encomendas = s.getEncomendas();
                std::vector<int> clientIdx;
                for (size_t i = 0; i < encomendas.size(); ++i) {
                    if (encomendas[i].getIdCliente() == idCliente) clientIdx.push_back(static_cast<int>(i));
                }
                if (clientIdx.empty()) {
                    std::cout << "Sem encomendas para este cliente.\n";
                    break;
                }
                std::cout << "Encomendas do cliente:\n";
                for (size_t k = 0; k < clientIdx.size(); ++k) {
                    const auto& e = encomendas[clientIdx[k]];
                    std::cout << "  [" << k << "] " << e.getDescricao() << " | " << nomeEstado(e.getEstado()) << "\n";
                }
                int escolha = lerInteiro("Escolha o indice da encomenda a cancelar: ");
                if (escolha < 0 || escolha >= static_cast<int>(clientIdx.size())) {
                    std::cout << "Indice invalido.\n";
                    break;
                }
                int idEnc = encomendas[clientIdx[escolha]].getId();
                if (s.cancelarEncomenda(idEnc)) std::cout << "Encomenda cancelada.\n";
                else                            std::cout << "Nao foi possivel cancelar ou encomenda nao existe.\n";
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
                int id = lerInteiro("ID do veiculo a remover: ");
                if (s.removerVeiculo(id)) std::cout << "Veiculo removido.\n";
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

}



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