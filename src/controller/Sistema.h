#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include <vector>

#include "../domain/Cliente.h"
#include "../domain/Deposito.h"
#include "../domain/Encomenda.h"
#include "../domain/Veiculo.h"

/**
 * Classe Sistema - Controlador (GRASP Controller / Pure Fabrication).
 *
 * Responsabilidades:
 *  - Receber pedidos vindos da camada de UI (main.cpp) e encaminha-los
 *    para as classes de dominio adequadas.
 *  - Manter as colecoes de Clientes, Depositos, Veiculos e Encomendas.
 *  - Atuar como Creator das Encomendas (GRASP Creator), uma vez que
 *    agrega-as e dispoe de todos os dados necessarios no momento da
 *    criacao.
 *  - Garantir a coerencia das transicoes de estado das encomendas
 *    (delegando em Encomenda::atualizarEstado).
 *
 * NAO e responsabilidade desta classe:
 *  - Apresentar menus, ler input do utilizador ou imprimir para o ecra.
 *    Essa responsabilidade pertence a camada de UI (main.cpp), que
 *    consome os metodos publicos abaixo e lida com a apresentacao.
 *
 * A ausencia de I/O dentro do Sistema e o que mantem o baixo
 * acoplamento entre a UI e o dominio (GRASP Low Coupling).
 */
class Sistema {
private:
    std::vector<Cliente>   clientes;
    std::vector<Deposito>  depositos;
    std::vector<Veiculo>   veiculos;
    std::vector<Encomenda> encomendas;

    // Contadores para gerar IDs unicos automaticamente.
    int proximoIdCliente;
    int proximoIdDeposito;
    int proximoIdEncomenda;

    // Metodos auxiliares privados - procuram entidades por identificador.
    // Devolvem ponteiro para o elemento dentro do vetor, ou nullptr se
    // nao existir. Os ponteiros so sao validos enquanto o vetor nao for
    // modificado, por isso sao usados apenas dentro de um unico metodo.
    Cliente*   procurarCliente(int id);
    Deposito*  procurarDeposito(int id);
    Veiculo*   procurarVeiculo(const std::string& matricula);
    Encomenda* procurarEncomenda(int id);

public:
    Sistema();

    // ---------- Gestao de Clientes ----------

    /**
     * Regista um novo cliente. Devolve o id atribuido (>= 1) em caso
     * de sucesso, ou -1 se os dados forem invalidos (nome vazio, etc.).
     */
    int registarCliente(const std::string& nome, const std::string& contacto);

    /** Remove o cliente com o id indicado. Devolve true em caso de sucesso. */
    bool removerCliente(int idCliente);

    // ---------- Gestao de Depositos ----------

    /**
     * Adiciona um novo deposito. Devolve o id atribuido ou -1 em caso
     * de erro (nome vazio, capacidade nao positiva, etc.).
     */
    int adicionarDeposito(const std::string& nome,
                          const std::string& localizacao,
                          int capacidadeMax);

    // ---------- Gestao de Veiculos ----------

    /**
     * Adiciona um novo veiculo a frota. Devolve true em caso de
     * sucesso. Falha se a matricula ja existir ou a capacidade for
     * invalida (regra de negocio do UC4).
     */
    bool adicionarVeiculo(const std::string& matricula, double capacidadeMax);

    /** Remove o veiculo com a matricula indicada. */
    bool removerVeiculo(const std::string& matricula);

    // ---------- Gestao de Encomendas (UC1) ----------

    /**
     * Cria uma nova encomenda associada a um cliente, com deposito
     * de origem e destino distintos. Tenta atribuir automaticamente
     * um veiculo disponivel com capacidade adequada; se nao for
     * possivel, a encomenda fica no estado Pendente (UC1, fluxo
     * alternativo 6a).
     *
     * Devolve o id da encomenda criada, ou -1 em caso de erro
     * (cliente inexistente, depositos iguais, peso <= 0, etc.).
     */
    int criarEncomenda(int idCliente,
                       int idDepOrigem,
                       int idDepDestino,
                       const std::string& descricao,
                       double peso);

    /**
     * Avanca o estado da encomenda para o "proximo" estado natural
     * do ciclo de vida (Atribuida -> Em Transporte -> Entregue).
     * Devolve true se a transicao foi efetuada.
     */
    bool avancarEstadoEncomenda(int idEncomenda);

    /** Cancela a encomenda. Falha se ja estiver entregue ou cancelada. */
    bool cancelarEncomenda(int idEncomenda);

    // ---------- Consultas (UC2 e UC3) ----------

    /**
     * Devolve uma string com a informacao completa do estado da
     * encomenda (UC2). Apenas a encomenda associada ao cliente
     * indicado pode ser consultada (regra de negocio do UC2).
     * Devolve string vazia se a encomenda nao existir ou nao
     * pertencer ao cliente.
     */
    std::string consultarEstadoEncomenda(int idEncomenda, int idCliente) const;

    // Acesso de leitura as colecoes para a camada de UI listar
    // (Consultar Informacao Global - UC3). Sao devolvidos por
    // referencia const para evitar copias e garantir imutabilidade.
    const std::vector<Cliente>&   getClientes()   const;
    const std::vector<Deposito>&  getDepositos()  const;
    const std::vector<Veiculo>&   getVeiculos()   const;
    const std::vector<Encomenda>& getEncomendas() const;
};

#endif // SISTEMA_H