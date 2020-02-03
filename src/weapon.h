//
// Created by matthew on 1/11/20.
//

#ifndef SRPG_ENGINE_WEAPON_H
#define SRPG_ENGINE_WEAPON_H

#include <cstdint>
#include <functional>
#include <memory>
#include "unit_attrs.h"

// TODO(matthew-c21): Add builders.

namespace srpg {

class Unit;

constexpr int INFINITE_DURABILITY = -1;

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

class Durability {
 public:
  virtual int remaining_durability() = 0;

  virtual int max_durability() = 0;

  virtual void reduce_durability() = 0;

  virtual void reduce_durability(int amount) = 0;

  virtual bool is_broken() = 0;

  virtual ~Durability() = default;
};

class InventoryItem {
 public:
  InventoryItem(const CoreStatSpread& bonuses, std::function<void(Unit&)> on_use) : stat_bonuses_(bonuses), on_use_(std::move(on_use)) {}

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

  virtual Durability& durability();

  virtual int required_rank() const;

  bool equipable() const override;

 protected:
  Equipable(int min_range, int max_range, int required_rank, std::unique_ptr<Durability> durability);

  Equipable(int min_range, int max_range, int required_rank, std::unique_ptr<Durability> durability,
            const CoreStatSpread& bonuses);

  Equipable(int min_range, int max_range, int required_rank, std::unique_ptr<Durability> durability,
            const CoreStatSpread& bonuses, std::function<void(Unit&)> on_use)
      : InventoryItem(bonuses, on_use), min_range_(min_range), max_range_(max_range), required_rank_(required_rank), durability_(std::move(durability)) {}

 private:
  const int min_range_, max_range_;
  const int required_rank_;

  std::unique_ptr<Durability> durability_;
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

  Weapon(WeaponType type, UnitAttribute effectiveness, std::unique_ptr<Durability> durability, int min_range, int max_range, int might, int weight,
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

/**
 * Special case of Consumable with unlimited durability.
 */
class Unbreakable : public Durability {
 public:
  Unbreakable();

  int remaining_durability() final;

  int max_durability() final;

  void reduce_durability() final;

  void reduce_durability(int amount) final;

  bool is_broken() final;
};

class Staff : public Equipable {
 public:
  Staff(int min_range, int max_range, int required_rank, std::unique_ptr<Durability> durability,
        std::function<int(Unit)> healing_formula)
    : Equipable(min_range, max_range, required_rank, std::move(durability)), healing_formula_(std::move(healing_formula)) {};

 private:
  const std::function<int(Unit)> healing_formula_;
};

}

#endif // SRPG_ENGINE_WEAPON_H
