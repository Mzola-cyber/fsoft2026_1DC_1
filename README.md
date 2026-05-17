# Sistema de Gestão de Encomendas — FSOFT 2025/2026

> Projeto académico — Unidade Curricular: Fundamentos de Desenvolvimento de Software (FSOFT)
> Instituto Superior de Engenharia do Porto (ISEP) — Ano letivo 2025/2026

══════════════════════════════════════════════════════════════════════════════

Índice rápido

- Visão geral
- Objetivos académicos
- Arquitetura e responsabilidades
- Funcionalidades implementadas
- Estrutura do repositório
- Como compilar e executar (Windows / Powershell)
- Notas de design: Recomendação de veículo
- Contribuição e autores

══════════════════════════════════════════════════════════════════════════════

Visão geral

Este repositório contém uma implementação em C++ (C++17) de um sistema simples
de gestão de encomendas. O foco pedagógico é demonstrar princípios de
orientação a objetos, separação de responsabilidades (UI / Controller / Domain / Service)
e pequenas decisões de design (por exemplo, serviço de recomendação como
"Pure Fabrication").

Objetivos académicos

- Praticar modelação de domínio e diagramas UML
- Implementar casos de uso (criar encomenda, atribuir veículo, consultar estado)
- Aplicar boas práticas de design (encapsulamento, responsabilidade única)

Arquitetura e responsabilidades

- main.cpp: camada de UI (input/output), simplicidade e validação de input
- controller/Sistema.*: controlador central — cria entidades e aplica regras de negócio
- domain/*: entidades do domínio (Cliente, Deposito, Veiculo, Encomenda)
- service/Recomendacao.*: serviço responsável por recomendar um veículo adequado

Funcionalidades implementadas (resumo)

- Registo de clientes
- Adição / remoção de depósitos e veículos
- Criação de encomendas (com validações: depósitos distintos, peso > 0)
- Atribuição automática de veículo (serviço Recomendacao)
- Avanço de estado da encomenda (Atribuída -> Em Transporte -> Entregue)
- Consulta de estado por cliente e listagens globais para administrador

Estrutura do repositório

```
fsoft2026_1DC_1/
├─ CMakeLists.txt
├─ README.md
├─ Documentation/
├─ src/
│  ├─ main.cpp
│  ├─ controller/Sistema.cpp, Sistema.h
│  ├─ domain/headers/*.h
│  ├─ domain/sources/*.cpp
│  └─ service/Recomendacao.*
```

Como compilar e executar (Windows - Powershell)

1. Criar diretório de build e invocar o CMake:

```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

2. Executar (a partir de build):

```powershell
.\GestaoEncomendas.exe
```

Nota: os comandos acima assumem uma toolchain compatível com CMake e um
compilador C++17 (MSVC, MinGW ou clang). O ficheiro CMakeLists.txt já
inclui os ficheiros principais do projeto.

Notas de design — Serviço Recomendação

O serviço `Recomendacao` (camada `service`) é responsável por isolar a
logica de seleção de um veículo adequado para uma encomenda. A implementação
actual procura um veículo disponível com capacidade suficiente e escolhe o
melhor ajuste (menor capacidade que ainda suporta o peso) — uma heurística
simples e eficaz para reduzir desperdício de capacidade.

Por que colocar isto numa camada separada?
- Evita que `Sistema` acumule lógica de optimização; melhora testabilidade;
- Segrega a responsabilidade (Single Responsibility Principle);
- Permite trocar a heurística (best-fit, first-fit, heurísticas por custo)
  sem alterar o controlador.

Por exemplo, a função pública exposta é:

```cpp
static int Recomendacao::recomendarVeiculo(const std::vector<Veiculo>& veiculos, double peso);
```

Retorna o id do veículo recomendado ou `-1` caso nenhum veículo adequado
esteja disponível.

Contribuição

- Use branches `feature/xxx` e pull requests para alterações.
- Documente decisões arquiteturais e mantenha a consistência com o UML
  produzido na pasta `Documentation`.

Autores

- Masembo Zola
- Mário Figueira
- David Soares

Referências académicas

- Larman, C. Applying UML and Patterns
- Sommerville, I. Software Engineering
- Material de apoio da UC FSOFT (ISEP)

