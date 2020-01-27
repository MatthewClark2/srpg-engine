//
// Created by matthew on 1/11/20.
//

#ifndef SRPG_ENGINE_WEAPON_H
#define SRPG_ENGINE_WEAPON_H

#include <cstdint>
#include <functional>
#include <memory>
#include "unit_attrs.h"

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
};

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
  InventoryItem(CoreStatSpread bonuses, std::function<void(Unit&)> on_use);

  CoreStatSpread stat_bonuses();

  void on_use(Unit& target);

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

 protected:
  Equipable(int min_range, int max_range, int required_rank, Durability* durability);

  Equipable(int min_range, int max_range, int required_rank, Durability* durability, CoreStatSpread bonuses);

  Equipable(int min_range, int max_range, int required_rank, Durability* durability, CoreStatSpread bonuses, std::function<void(Unit&)> on_use)
      : InventoryItem(bonuses, std::move(on_use)), min_range_(min_range), max_range_(max_range), required_rank_(required_rank), durability_(durability) {}

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
  MovementType effectiveness() const;

  /**
   * Create a 1 range weapon.
   */
  Weapon(WeaponType, MovementType, int, int, int, int, int, bool);

  /**
   * Construct a new weapon with a custom range.
   */
  Weapon(WeaponType, MovementType, int, int, int, int, int, int, int, bool);

 private:
  WeaponType type_;
  MovementType effectiveness_;
  int might_;
  int weight_;
  int accuracy_;
  int critical_;
  int required_rank_;
  bool is_magic_;
};

/**
 * Special case of Consumable with unlimited durability.
 */
class Unbreakable : public Durability {
 public:
  int remaining_durability() final;

  int max_durability() final;

  void reduce_durability() final;

  void reduce_durability(int amount) final;

  bool is_broken() final;
};

class Staff : public Equipable {
 public:
  Staff(int min_range, int max_range, int required_rank, Durability* durability, std::function<int(Unit)> healing_formula)
    : Equipable(min_range, max_range, required_rank, durability), healing_formula_(std::move(healing_formula)) {};

 private:
  const std::function<int(Unit)> healing_formula_;
};

}

#endif // SRPG_ENGINE_WEAPON_H
