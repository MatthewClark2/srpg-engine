//
// Created by matthew on 1/11/20.
//

#include <memory>

// Temporarily.
#include <exception>

#include "unit.h"
#include "unit_attrs.h"


namespace srpg {

// TODO(matthew-c21): Move relevant implementations to unit_attrs.cpp when convenient.

// TODO(matthew-c21): Inline these once they have been tested.

Unit::Unit(CoreStatSpread baseStats, CoreStatSpread growths, UnitAttribute attributes, const UnitClass& clazz,
           int baseWeaponRank)
    : base_attributes_(attributes), growths_(growths), rnk_(baseWeaponRank), stats_(baseStats),
    clazz_(clazz), equipped_(false), level_(1), exp_(0) {
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

Equipable* Unit::held_item() {
  return nullptr;
}

const Equipable* Unit::held_item() const {
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

UnitClass::UnitClass(CoreStatSpread stats, MovementType mov, UnitAttribute attrs, WeaponType weps)
    : stat_bonuses(stats), movement_type(mov), class_attributes(attrs), usable_weapon_types(weps) {
}

} // namespace srpg
