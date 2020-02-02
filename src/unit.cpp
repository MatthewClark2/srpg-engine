//
// Created by matthew on 1/11/20.
//

#include <memory>

// Temporarily.
#include <exception>

#include "unit.h"
#include "unit_attrs.h"


namespace srpg {

Unit::Unit(const CoreStatSpread& base_stats, const CoreStatSpread& growths, UnitAttribute attributes,
    const UnitClass& clazz, int base_weapon_rank)
    : Unit(base_stats, growths, attributes, clazz, base_weapon_rank, 0, 1) {
}

int Unit::rnk() const {
  return 0;
}

int Unit::exp() const {
  return 0;
}

int Unit::level() const {
  return 0;
}

bool Unit::is_equipped() const {
  return false;
}

void Unit::unequip() {

}

bool Unit::equip() {
  return false;
}

bool Unit::has_attributes(UnitAttribute attributes) const {
  return false;
}

bool Unit::give_exp(int exp) {
  return false;
}

bool Unit::give_exp(int exp, bool& failed) {
  return false;
}

CoreStatSpread Unit::stats() const {
  return CoreStatSpread(0, 0, 0, 0, 0, 0, 0);
}

UnitAttribute Unit::attributes() const {
  return UnitAttribute::Beastial;
}

const UnitClass& Unit::clazz() const {
  throw std::exception();
}

InventoryItem* Unit::held_item() {
  return nullptr;
}

const InventoryItem* Unit::held_item() const {
  return nullptr;
}

std::unique_ptr<InventoryItem> Unit::drop_item(bool& successful) {
  return nullptr;
}

void Unit::give_item(InventoryItem& item) {

}

bool Unit::dead() const {
  return false;
}

void Unit::offset_hp(int amount) {

}

void Unit::buff(CoreStatSpread mod) {

}

Weapon* Unit::equipped_weapon() {
  return nullptr;
}

const Weapon* Unit::equipped_weapon() const {
  return nullptr;
}

int Unit::remaining_hp() const {
  return 0;
}

bool Unit::can_equip() const {
  return false;
}

bool Unit::can_equip(const Weapon& weapon) const {
  return false;
}

Unit::Unit(const CoreStatSpread& base_stats, const CoreStatSpread& growths, UnitAttribute attributes,
    const UnitClass& clazz, int base_weapon_rank, int base_exp) : Unit(base_stats, growths, attributes, clazz,
        base_weapon_rank, base_exp, 1) {

}

Unit::Unit(const CoreStatSpread& base_stats, const CoreStatSpread& growths, UnitAttribute attributes,
    const UnitClass& clazz, int base_weapon_rank, int base_exp, int base_level)
    : stats_(base_stats), growths_(growths), base_attributes_(attributes), clazz_(clazz), rnk_(base_weapon_rank),
    exp_(base_exp), base_level_(base_level), levels_gained_(0) {
  remaining_hp_ = base_stats.hp;
}

UnitClass::UnitClass(const CoreStatSpread& stats, MovementType mov, UnitAttribute attrs, WeaponType weps)
    : stat_bonuses(stats), movement_type(mov), class_attributes(attrs), usable_weapon_types(weps) {
}

} // namespace srpg
