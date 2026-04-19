# fsoft2026_1DC_1

## Sistema de Gestao de Encomendas

> Projeto academico da UC **Fundamentos de Desenvolvimento de Software (FSOFT)**  
> **Instituto Superior de Engenharia do Porto (ISEP)**  
> Ano letivo **2025/2026**

---

## Navegacao rapida

- [Visao geral](#visao-geral)
- [Objetivos academicos](#objetivos-academicos)
- [Atores do sistema](#atores-do-sistema)
- [Funcionalidades previstas](#funcionalidades-previstas)
- [Engenharia de software e artefactos](#engenharia-de-software-e-artefactos)
- [Estrutura do repositorio](#estrutura-do-repositorio)
- [Roadmap por iteracao](#roadmap-por-iteracao)
- [Build, execucao e testes](#build-execucao-e-testes)
- [Contribuicao](#contribuicao)
- [Autores e referencias](#autores-e-referencias)

---

## Visao geral

Este repositorio descreve o desenvolvimento de um sistema em **C++** para registo, acompanhamento e administracao de encomendas, com foco em modelacao orientada a objetos e controlo logistico.

O sistema procura suportar:

- Gestao de clientes e encomendas
- Definicao de depositos de origem e destino
- Gestao de veiculos e respetiva disponibilidade
- Atribuicao de transporte e monitorizacao de estado

## Objetivos academicos

| Dimensao | Foco |
|---|---|
| Engenharia de Requisitos | User Stories, requisitos funcionais e nao funcionais |
| Analise e Design | Modelacao UML e definicao da arquitetura |
| Implementacao | Desenvolvimento incremental em C++ |
| Qualidade | Testes, consistencia de dados e rastreabilidade |

## Atores do sistema

### Cliente

- Criar encomendas
- Selecionar deposito de origem e destino
- Consultar o estado das suas encomendas

### Administrador

- Adicionar e remover veiculos
- Remover clientes
- Consultar informacao global do sistema

## Funcionalidades previstas

- Registar e gerir clientes
- Criar encomendas com origem e destino
- Consultar estado das encomendas
- Gerir frota de veiculos
- Atribuir automaticamente veiculos disponiveis
- Disponibilizar visao global para administracao

## Engenharia de software e artefactos

Artefactos previstos ao longo das iteracoes:

- User Stories
- Requisitos funcionais e nao funcionais (FURPS+)
- Domain Model
- Use Case Diagram e Use Case Specifications
- System Sequence Diagrams (SSD)
- Diagramas de Design (classes, sequencia, componentes, deployment)

## Estrutura do repositorio

```text
fsoft2026_1DC_1/
|-- Documentation/
|   |-- Iteration01/
|   |   |-- Technical Report.docx
|   |   `-- Technical Report.pdf
|   |-- Iteration02/
|   `-- Iteration03/
|-- Project/
|-- ProjectTester/
`-- README.md
```

> Estado atual: `Project/` e `ProjectTester/` ainda nao contem codigo-fonte neste repositorio.

## Roadmap por iteracao

| Iteracao | Objetivo principal | Estado esperado |
|---|---|---|
| `Iteration01` | Levantamento de requisitos e base documental | Concluida (documentacao inicial) |
| `Iteration02` | Consolidacao de analise/design e evolucao da arquitetura | Em progresso |
| `Iteration03` | Implementacao, testes e estabilizacao | Planeada |

## Build, execucao e testes

No estado atual do repositorio, ainda nao existe configuracao oficial de build (por exemplo, `CMakeLists.txt`).

Quando a base de codigo estiver disponivel, esta secao deve incluir:

- Pre-requisitos (compilador, versoes e ferramentas)
- Comandos de compilacao
- Comandos de execucao
- Comandos de testes unitarios e de integracao

## Contribuicao

Fluxo recomendado para colaboracao:

1. Criar uma branch por funcionalidade (`feature/nome-curto`)
2. Fazer commits pequenos, coerentes e descritivos
3. Abrir Pull Request com contexto tecnico e impacto
4. Atualizar documentacao sempre que houver alteracoes relevantes

## Tecnologias

- Linguagem: C++
- Paradigma: Orientacao a Objetos
- Modelacao: UML
- Versionamento: Git/GitHub

## Autores e referencias

### Autores

- Masembo Zola
- Mario Figueira
- David Soares

Licenciatura em Engenharia de Telecomunicacoes e Informatica  
Instituto Superior de Engenharia do Porto (ISEP)

### Referencias

- Larman, C. *Applying UML and Patterns*.
- Sommerville, I. *Software Engineering*.
- OMG. *Unified Modeling Language (UML)*.
- Material de apoio da UC FSOFT (ISEP).
