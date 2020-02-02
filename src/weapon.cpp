//
// Created by matthew on 1/11/20.
//

#include <exception>
#include "weapon.h"

namespace srpg {

static void nop(Unit& _u) {}

InventoryItem::InventoryItem(const CoreStatSpread& bonuses, std::function<void(Unit&)> on_use) {

}

CoreStatSpread InventoryItem::stat_bonuses() {
  return CoreStatSpread();
}

void InventoryItem::on_use(Unit& target) {

}

std::tuple<int, int> Equipable::get_range() const {
  return std::tuple<int, int>();
}

Durability& Equipable::durability() {
  throw std::exception();
}

int Equipable::required_rank() const {
  return 0;
}

Equipable::Equipable(int min_range, int max_range, int required_rank, std::unique_ptr<Durability> durability)
    : Equipable(min_range, max_range, required_rank, std::move(durability), CoreStatSpread()) {

}

Equipable::Equipable(int min_range, int max_range, int required_rank, std::unique_ptr<Durability> durability,
                     const CoreStatSpread& bonuses) : InventoryItem(bonuses, &nop), min_range_(min_range),
    max_range_(max_range), required_rank_(required_rank), durability_(std::move(durability)) {

}

WeaponType Weapon::type() const {
  return WeaponType::Lance;
}

int Weapon::might() const {
  return 0;
}

int Weapon::weight() const {
  return 0;
}

int Weapon::accuracy() const {
  return 0;
}

int Weapon::critical() const {
  return 0;
}

bool Weapon::is_magic() const {
  return false;
}

UnitAttribute Weapon::effectiveness() const {
  return UnitAttribute::Beastial;
}

Weapon::Weapon(WeaponType type, UnitAttribute effectiveness, int might, int weight,
               int accuracy, int critical, int required_rank, bool is_magic) : Weapon(type, effectiveness, 0, 0, might,
                                                                                      weight, accuracy, critical,
                                                                                      required_rank, is_magic) {

}

Weapon::Weapon(WeaponType type, UnitAttribute effectiveness, int min_range, int max_range, int might, int weight,
               int accuracy, int critical, int required_rank, bool is_magic) : Weapon(type, effectiveness,
                                                                                      std::make_unique<Unbreakable>(),
                                                                                      min_range, max_range, might,
                                                                                      weight,
                                                                                      accuracy, critical, required_rank,
                                                                                      is_magic) {

}

Weapon::Weapon(WeaponType type, UnitAttribute effectiveness, std::unique_ptr<Durability> durability, int min_range,
               int max_range, int might, int weight, int accuracy, int critical, int required_rank, bool is_magic)
    : Equipable(min_range, max_range, required_rank, std::move(durability)), type_(type), effectiveness_(effectiveness),
    might_(might), weight_(weight), accuracy_(accuracy), critical_(critical), is_magic_(is_magic) {

}

Unbreakable::Unbreakable() {

}

int Unbreakable::remaining_durability() {
  return 0;
}

int Unbreakable::max_durability() {
  return 0;
}

void Unbreakable::reduce_durability() {

}

void Unbreakable::reduce_durability(int amount) {

}

bool Unbreakable::is_broken() {
  return false;
}

}  // end namespace srpg
