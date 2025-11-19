#pragma once
#include <string>
#include <iostream> // Necessário para std::string

// Declaramos o struct
struct Item {
    // Propriedades (Variáveis)
    std::string name;
    int count;
    double cpsPerItem;
    double baseCost;
    double currentCost;
    double costMultiplier;
    float currentMultiplier;

    // Declaração do Construtor (Note o ponto e vírgula no final, sem {})
    Item(std::string n, double cps, double cost);

    // Declaração dos Métodos
    double GetContribuition();
    void Buy(double& playerCur);
};