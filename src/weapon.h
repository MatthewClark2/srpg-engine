//
// Created by matthew on 1/11/20.
//

#ifndef SRPG_ENGINE_WEAPON_H
#define SRPG_ENGINE_WEAPON_H

#include <cstdint>
#include <functional>
#include "unit.h"

namespace srpg {

    enum class WeaponType {
        Axe = 0x01,
        Tome = 0x02,
        Lance = 0x04,
        Sword = 0x08,
        Stone = 0x10,
        Staff = 0x20,
    };

    constexpr WeaponType operator|(WeaponType a, WeaponType b);

    bool operator==(WeaponType a, WeaponType b);

// TODO(matthew-c21): Consider refactoring to a component to avoid issues with subclassing for unbreakable weapons.
    struct Consumable {
        virtual int remainingDurability() = 0;

        virtual int maxDurability() = 0;

        virtual bool reduceDurability() = 0;

        virtual bool isBroken() = 0;
    };

    struct InventoryItem {
        virtual void hpBonus() = 0;

        virtual void powBonus() = 0;

        virtual void defBonus() = 0;

        virtual void resBonus() = 0;

        virtual void sklBonus() = 0;

        virtual void lukBonus() = 0;

        virtual void spdBonus() = 0;
    };

    struct Equipable {
        const int minRange, maxRange;

    protected:
        Equipable(int minRange, int maxRange) : minRange(minRange), maxRange(maxRange) {}
    };

// TODO: make an unbreakable weapon type.
    struct Weapon : public Equipable, Consumable {
        const WeaponType type;
        const int might;
        const int weight;
        const int accuracy;
        const bool isMagic;
        int durability;
        const MovementType effectiveness;
        const int requiredRank;
    };

/// Special instance of @class{Weapon} that features unlimited durability.
    class UnbreakableWeapon : Weapon {
    };

    struct Staff : public Equipable {
        const int requiredRank;
        // const std::function<int(Unit)> healingFormula;
    };

}

#endif // SRPG_ENGINE_WEAPON_H
