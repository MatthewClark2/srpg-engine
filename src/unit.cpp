//
// Created by matthew on 1/11/20.
//

#include "unit.h"

// TODO(matthew-c21): Inline these once they have been tested.
MovementType operator|(MovementType a, MovementType b) {
    return static_cast<MovementType>(uint32_t(a) | uint32_t(b));
}

bool operator==(MovementType a, MovementType b) {
    return (uint32_t(a) & uint32_t(b)) != 0U;
}
