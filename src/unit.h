//
// Created by matthew on 1/11/20.
//

#ifndef SRPG_ENGINE_UNIT_H
#define SRPG_ENGINE_UNIT_H

#include <cstdint>
#include <optional>
#include <unordered_set>
#include <memory>
#include "unit_attrs.h"
#include "weapon.h"

namespace srpg {

// TODO(matthew-c21): These will ultimately want to be project level constants rather than engine level ones.
constexpr int EXP_PER_LEVEL = 100;
constexpr int MAX_LEVEL = 20;

/**
 * Classes should be defined globally, and passed around by const reference.
 *
 * UnitClasses have static lifetimes within the context of an SRPG project. As such, no class or method that uses them
 * should have ownership of them outside of the global context in which they are made. However, since Units are able to
 * change classes, they need to be able to rebind their own class according to some metric. This means I need an
 * external reclassing logic. A class should have some set of classes that it can promote to, with the ability to select
 * from those promotions, then apply it back to the original unit.
 *
 * As much as I don't want to, a raw pointer seems to be the best solution. It doesn't attempt to manage its own memory
 * like a shared_ptr does, and can be rebound unlike a reference.
 */
struct UnitClass {
  const CoreStatSpread stat_bonuses;
  const MovementType movement_type;
  const UnitAttribute class_attributes;
  const WeaponType usable_weapon_types;

  // TODO(matthew-c21): Name these better. Applies to cpp file as well.
  UnitClass(const CoreStatSpread& stats, MovementType mov, UnitAttribute attrs, WeaponType weps);
};

class Unit {
 public:
  Unit(const CoreStatSpread& base_stats, const CoreStatSpread& growths, UnitAttribute attributes,
      const UnitClass& clazz, int baseWeaponRank);

  Unit(const CoreStatSpread& base_stats, const CoreStatSpread& growths, UnitAttribute attributes,
      const UnitClass& clazz, int base_weapon_rank, int base_exp);

  Unit(const CoreStatSpread& base_stats, const CoreStatSpread& growths, UnitAttribute attributes,
      const UnitClass& clazz, int base_weapon_rank, int base_exp, int base_level);

  int rnk() const;

  int exp() const;

  int level() const;

  /**
   * Obtain the remaining health of this unit. The value will never be greater than stats.hp, or lower than 0.
   */
  int remaining_hp() const;

  bool is_equipped() const;

  /**
   * Remove the unit's currently equipped item. Does nothing if the unit is not holding anything.
   */
  void unequip();

  /**
   * Attempt to equip the item held by the unit. Does nothing if the unit is already holding their item, or if there is
   * no item to equip.
   * @return the status of whether or not the unit is equipped after the operation.
   */
  bool equip();

  /**
   * Determine whether or not the unit can equip their currently held item. Functionally identical to
   * @code{can_equip(this->item);}.
   * @return false if the item is not an instance of Equipable, if it is of an inappropriate weapon type, or if the unit
   *    lacks the required weapon rank.
   */
  bool can_equip() const;

  /**
   * Determine whether or not the unit can equip the provided item without actually doing so.
   */
  bool can_equip(const Weapon& weapon) const;

  /**
   * Determines whether or not the given attributes form a subset of the unit's own attributes.
   * @param attributes a UnitAttribute
   * @return true if the unit has all of the given attributes, and false otherwise.
   */
  bool has_attributes(UnitAttribute attributes) const;

  /**
   * Return a mutable pointer to the underlying held item. The lifetime of this pointer is managed by this object unless
   * moved by a trade or discard action.
   * @return a pointer to this unit's held item, or nullptr of one isn't present.
   */
  InventoryItem* held_item();

  const InventoryItem* held_item() const;

  Weapon* equipped_weapon();

  const Weapon* equipped_weapon() const;

  /**
   * Take the item currently held by the unit. Returns nullptr if the unit is holding nothing.
   * @param [in] successful set to true if the operation returned a non-nullptr value, false if nullptr is returned.
   * @return transferred ownership of the unit's held item.
   */
  std::unique_ptr<InventoryItem> drop_item(bool& successful);

  /**
   * Give an item to the unit. If the unit is already holding an item, it will be discarded and replaced.
   * @param item the new item that the unit should hold.
   */
  void give_item(InventoryItem& item);

  /**
   * Similar to #giveExperience(int, bool), but discards the output parameter.
   */
  bool give_exp(int exp);

  /**
   * Grant this unit some amount of experience, responding with whether or not this unit gained a level in doing so.
   * @param exp the experience earned. If the value is greater than #EXP_PER_LEVEL, it will be capped.
   * @param [out] failed an out parameter telling whether or not experience was successfully given.
   * @return true if gaining EXP resulted in a level up, and false otherwise.
   */
  bool give_exp(int exp, bool &failed);

  /**
   * Get the stats of this unit after applying bonuses from equipment and class.
   * @return the unit's effective stats.
   */
  CoreStatSpread stats() const;

  /**
   * @return the attributes of this unit after applying class attributes.
   */
  UnitAttribute attributes() const;

  const UnitClass& clazz() const;

  /**
   * Determine whether or not this unit is capable of combat. Generally speaking, this only happens when a unit dies,
   * although there are plans to leave script triggers to disable units.
   * @return true if the unit should be removed from the map.
   */
  bool dead() const;

  /**
   * Restore health or inflict damage, depending on the sign of amount. Health cannot become negative.
   * @param amount the amount of health to be restored or damage inflicted.
   */
  void offset_hp(int amount);

  /**
   * Apply (de)buffs. These are persistent. Should a negative buff be greater than the actual stat, the value will be
   * capped at 0 (1 for HP). Note that HP (de)buffs only apply to max HP, not currently remaining HP.
   * @param mod total (de)buffs across all stats.
   */
  void buff(CoreStatSpread mod);

  /*
   * Disabled until reclassing is enabled.
   *
   * Generates a new unit representing the current unit after changing to the given class. If the given class is not in
   * this unit's base class set or promoted class sets, then the operation fails.
   *
   * This method does not modify the current unit.
   * @param new_class the unit's new class. This should belong to a unit's class set.
   * @return Ok(Unit) if the operation succeeds. None otherwise.
   */
  // std::optional<Unit> clazz(const UnitClass& new_class);

 private:
  // Stats are just base stats
  CoreStatSpread stats_;
  CoreStatSpread buffs_;
  const CoreStatSpread growths_;
  int rnk_, base_level_, levels_gained_, exp_;
  int remaining_hp_;

  const UnitAttribute base_attributes_;

  // TODO(matthew-c21): Find a better data type for this when reclassing becomes available.
  const UnitClass& clazz_;

  // I'd like an inventory system like Gaiden since it's both easier to handle, and adds a new layer of inventory
  // management not found in most of the games.
  std::unique_ptr<Equipable> inventory_;

  bool equipped_;
};

} // namespace srpg

#endif //SRPG_ENGINE_UNIT_H
