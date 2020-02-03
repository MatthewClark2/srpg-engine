//
// Created by matthew on 1/11/20.
//

#include <exception>
#include "weapon.h"

namespace srpg {

static void nop(Unit& _u) {}

WeaponType operator|(WeaponType left, WeaponType right) {
  return WeaponType(static_cast<unsigned int>(left) | static_cast<unsigned int>(right));
}

WeaponType operator&(WeaponType left, WeaponType right) {
  return WeaponType(static_cast<unsigned int>(left) & static_cast<unsigned int>(right));
}

CoreStatSpread InventoryItem::stat_bonuses() const {
  return stat_bonuses_;
}

void InventoryItem::on_use(Unit& target) {
  on_use_(target);
}

bool InventoryItem::equipable() const {
  return false;
}

std::tuple<int, int> Equipable::get_range() const {
  return std::tuple<int, int>(min_range_, max_range_);
}

Durability& Equipable::durability() {
  return *durability_;
}

int Equipable::required_rank() const {
  return required_rank_;
}

Equipable::Equipable(int min_range, int max_range, int required_rank, std::unique_ptr<Durability> durability)
    : Equipable(min_range, max_range, required_rank, std::move(durability), CoreStatSpread()) {

}

Equipable::Equipable(int min_range, int max_range, int required_rank, std::unique_ptr<Durability> durability,
                     const CoreStatSpread& bonuses) : InventoryItem(bonuses, &nop), min_range_(min_range),
    max_range_(max_range), required_rank_(required_rank), durability_(std::move(durability)) {

}

bool Equipable::equipable() const {
  return true;
}

WeaponType Weapon::type() const {
  return type_;
}

int Weapon::might() const {
  return might_;
}

int Weapon::weight() const {
  return weight_;
}

int Weapon::accuracy() const {
  return accuracy_;
}

int Weapon::critical() const {
  return critical_;
}

bool Weapon::is_magic() const {
  return is_magic_;
}

UnitAttribute Weapon::effectiveness() const {
  return effectiveness_;
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
  return INFINITE_DURABILITY;
}

int Unbreakable::max_durability() {
  return INFINITE_DURABILITY;
}

void Unbreakable::reduce_durability() {}

void Unbreakable::reduce_durability(int amount) {}

bool Unbreakable::is_broken() {
  return false;
}

}  // end namespace srpg
