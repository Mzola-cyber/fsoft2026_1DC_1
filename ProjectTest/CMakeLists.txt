add_executable(runTests
        # TESTS
        ClienteServiceTest.cpp
        DepositoServiceTest.cpp
        VeiculoServiceTest.cpp
        SistemaControllerTest.cpp
        EncomendaServiceTest.cpp
        DomainTest.cpp


        # CONTROLLER
        ../src/controller/Sistema.cpp

        #View
        ../src/View/sources/ClienteView.cpp
        ../src/View/sources/AdministradorView.cpp
        ../src/View/sources/MenuView.cpp
        ../src/View/sources/UtilsView.cpp

        # SERVICES
        ../src/service/sources/RecomendacaoService.cpp
        ../src/service/sources/EncomendaService.cpp
        ../src/service/sources/VeiculoService.cpp
        ../src/service/sources/ClienteService.cpp
        ../src/service/sources/DepositoService.cpp

        # REPOSITORIES
        ../src/repository/sources/VeiculoRepository.cpp
        ../src/repository/sources/EncomendaRepository.cpp
        ../src/repository/sources/ClienteRepository.cpp
        ../src/repository/sources/DepositoRepository.cpp

        # DOMAIN
        ../src/domain/sources/Encomenda.cpp
        ../src/domain/sources/Veiculo.cpp
        ../src/domain/sources/Cliente.cpp
        ../src/domain/sources/Deposito.cpp

        # MAPPERS
        ../src/mappers/sources/EncomendaMapper.cpp
        ../src/mappers/sources/VeiculoMapper.cpp
        ../src/mappers/sources/ClienteMapper.cpp
        ../src/mappers/sources/DepositoMapper.cpp

)

target_link_libraries(runTests
        gtest
        gtest_main
)

add_test(NAME runTests COMMAND runTests)