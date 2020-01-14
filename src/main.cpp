#include <iostream>
#include "unit.h"

using namespace srpg;

int main() {
    std::cout << "Hello, World!" << std::endl;
    auto greatKnight = MovementType::Armored | MovementType::Cavalry;
    return 0;
}