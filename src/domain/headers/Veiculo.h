
#ifndef FSOFT_VEICULO_H
#define FSOFT_VEICULO_H

#include <string>

class Veiculo {
private:
    int idVeiculo;
    std::string matricula;
    double capacidadeMax;
    bool disponivel;

public:
    Veiculo(int idVeiculo, std::string matricula, double capacidadeMax);
    std::string getMatriculaVeiculo() const;
    int getId() const;
    bool estaDisponivel() const;
    double getCapacidade() const;
    void setDisponivel(bool disponivel);
};

#endif
