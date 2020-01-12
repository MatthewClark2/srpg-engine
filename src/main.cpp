#include <iostream>
#include "unit.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto greatKnight = MovementType::Armored | MovementType::Cavalry;
    return 0;
}