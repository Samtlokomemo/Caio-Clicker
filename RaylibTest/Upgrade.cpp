#include "Upgrade.h"

Upgrade::Upgrade(std::string n, double c, upgradeType t, float m, int target)
    : name(n), cost(c), type(t), multiplier(m), targetItemIndex(target) {
};