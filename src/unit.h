//
// Created by matthew on 1/11/20.
//

#ifndef FIRE_ENGINE_UNIT_H
#define FIRE_ENGINE_UNIT_H

#include <cstdint>
#include <optional>
#include <bits/unique_ptr.h>

struct InventoryItem;
struct Equipable;

enum class MovementType {
    Flying   = 0x01,
    Cavalry  = 0x02,
    Brigand  = 0x04,
    Armored  = 0x08,
    Infantry = 0x10,
};

MovementType operator|(MovementType a, MovementType b);
bool operator==(MovementType a, MovementType b);

// TODO(matthew-c21): I want split weapon/item inventories, like in the GC games.
class Unit {
    int hp, pow, def, res, luk, skl, spd, rnk;

public:
    int hpGrowth, powGrowth, defGrowth, resGrowth, lukGrowth, sklGrowth, spdGrowth;
    std::optional<std::unique_ptr<Equipable>> equipment;  // The alternative is a nullable ptr, and I'd rather not.
    std::unique_ptr<InventoryItem> inventory[5];

    int getHp() const;
    int getPow() const;
    int getDef() const;
    int getRes() const;
    int getLuk() const;
    int getSkl() const;
    int getSpd() const;
    int getRnk() const;
};

#endif //FIRE_ENGINE_UNIT_H
