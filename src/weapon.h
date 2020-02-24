#ifndef SRPG_ENGINE_WEAPON_H
#define SRPG_ENGINE_WEAPON_H

#include <cstdint>
#include <functional>
#include <memory>
#include <utility>
#include "unit_attrs.h"

// TODO(matthew-c21): Add builders.

namespace srpg {

class Unit;

enum class WeaponType {
  Axe = 0x01,
  Tome = 0x02,
  Lance = 0x04,
  Sword = 0x08,
  Stone = 0x10,
  Staff = 0x20,
  None = 0x00,
};

WeaponType operator|(WeaponType left, WeaponType right);

WeaponType operator&(WeaponType left, WeaponType right);

class InventoryItem {
 public:
  InventoryItem(const CoreStatSpread& bonuses, std::function<void(Unit&)> on_use) : stat_bonuses_(bonuses),
      on_use_(std::move(on_use)) {}

  CoreStatSpread stat_bonuses() const;

  /**
   *
   * @return
   */
  virtual bool equipable() const;

  virtual void on_use(Unit& target);

  virtual ~InventoryItem() = default;

 private:
  CoreStatSpread stat_bonuses_;
  std::function<void(Unit&)> on_use_;
};

class Equipable : public InventoryItem {
 public:
  virtual std::tuple<int, int> get_range() const;

  virtual int required_rank() const;

  bool equipable() const override;

 protected:
  Equipable(int min_range, int max_range, int required_rank);

  Equipable(int min_range, int max_range, int required_rank, const CoreStatSpread& bonuses);

  Equipable(int min_range, int max_range, int required_rank, const CoreStatSpread& bonuses,
            std::function<void(Unit&)> on_use)
      : InventoryItem(bonuses, std::move(on_use)), min_range_(min_range), max_range_(max_range),
      required_rank_(required_rank) {}

 private:
  const int min_range_, max_range_;
  const int required_rank_;
};

class Weapon : public Equipable {
 public:
  WeaponType type() const;

  int might() const;

  int weight() const;

  int accuracy() const;

  int critical() const;

  bool is_magic() const;

  UnitAttribute effectiveness() const;

  /**
   * Create a 1 range weapon.
   */
  Weapon(WeaponType type, UnitAttribute effectiveness, int might, int weight,
         int accuracy, int critical, int required_rank, bool is_magic);

  /**
   * Construct a new weapon with a custom range.
   */
  Weapon(WeaponType type, UnitAttribute effectiveness, int min_range, int max_range, int might, int weight,
         int accuracy, int critical, int required_rank, bool is_magic);

 private:
  WeaponType type_;
  UnitAttribute effectiveness_;
  int might_;
  int weight_;
  int accuracy_;
  int critical_;
  bool is_magic_;
};

class Staff : public Equipable {
 public:
  Staff(int min_range, int max_range, int required_rank, std::function<int(Unit)> healing_formula)
      : Equipable(min_range, max_range, required_rank),
      healing_formula_(std::move(healing_formula)) {};

 private:
  const std::function<int(Unit)> healing_formula_;
};

}

#endif // SRPG_ENGINE_WEAPON_H
