#include "Item.h"

// Implementação do Construtor
// Usamos "Item::" para dizer que essa função pertence ao struct Item
Item::Item(std::string n, double cps, double cost) {
    name = n;
    cpsPerItem = cps;
    baseCost = cost;
    currentCost = cost;
    count = 0;           // Valores padrão
    costMultiplier = 1.15;
    currentMultiplier = 1.0f;
}

// Implementação do GetContribuition
double Item::GetContribuition() {
    return (double)count * cpsPerItem * currentMultiplier;
}

// Implementação do Buy
void Item::Buy(double& playerCur) {
    if (playerCur >= currentCost) {
        playerCur -= currentCost;
        count++;
        currentCost *= costMultiplier;
    }
}