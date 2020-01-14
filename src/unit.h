//
// Created by matthew on 1/11/20.
//

#ifndef SRPG_ENGINE_UNIT_H
#define SRPG_ENGINE_UNIT_H

#include <cstdint>
#include <optional>
#include <unordered_set>
#include <bits/unique_ptr.h>

namespace srpg {

// TODO(matthew-c21): These will ultimately want to be project level constants rather than engine level ones.
constexpr int MAX_INVENTORY_SIZE = 5;
constexpr int EXP_PER_LEVEL = 100;
constexpr int MAX_LEVEL = 20;

struct InventoryItem;
struct Equipable;
enum class WeaponType;

enum class MovementType {
  Flying,
  Cavalry,
  Infantry,
};

/**
 * Character attributes, partially modified by the unit's class. These may be combined bitwise in order to define a unit
 * with multiple attributes. For example, Tiki on a pegasus would be both Draconic and Flying.
 */
enum class UnitAttribute {
  Winged = 0x01,
  Armored = 0x02,
  Draconic = 0x04,
  Beastial = 0x08,
  None = 0x00,
};

/**
 * Centralized definition of core stats. This struct may be used to define baselines, growths, and bonuses. Its
 * existence is justified by the fact that all units have a set of stats and growths for said stats, most items can
 * provide bonuses to said stats, and classes come with stat modifiers. Having a single interface just reduces code
 * clutter, although it does require copies to be made frequently, which may impact performance slightly when compared
 * to single integers.
 */
struct CoreStatSpread {
  int hp, atk, def, res, luk, skl, spd;

  CoreStatSpread(int hp, int atk, int def, int res, int luk, int skl, int spd)
      : hp(hp), atk(atk), def(def), res(res), luk(luk), skl(skl), spd(spd) {}
};

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
  UnitClass(CoreStatSpread stats, MovementType mov, UnitAttribute attrs, WeaponType weps);
};

class Unit {
 public:
  Unit(CoreStatSpread baseStats, CoreStatSpread growths, UnitAttribute attributes, const UnitClass& clazz,
      int baseWeaponRank);

  int rnk() const;

  int exp() const;

  int level() const;

  bool is_equipped() const;

  /**
   * Remove the unit's currently equipped item. Does nothing if the unit is not holding anything.
   */
  void unequip();

  /**
   * Attempt to equip the item at the provided index. Does nothing on failure.
   * @param pos the position of the desired equipable item.
   * @return true if the operation succeeds. False if the index is out of bounds or points to an element that the unit
         cannot naturally equip.
   */
  bool equip(int pos);

  /**
   * Determines whether or not the given attributes form a subset of the unit's own attributes.
   * @param attributes a UnitAttribute
   * @return true if the unit has all of the given attributes, and false otherwise.
   */
  bool has_attributes(UnitAttribute attributes) const;

  std::optional<std::shared_ptr<Equipable>> equipped_item();

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
  CoreStatSpread stats_;
  const CoreStatSpread growths_;
  int rnk_, level_, exp_;

  const UnitAttribute base_attributes_;
  const UnitClass& clazz_;

  // Shared pointers are needed since the existence of these items are tied to the unit that has them. In particular,
  // references may be held by the unit, damage calculation, and display engine simultaneously. However, the general
  // case will be a single instance of any given shared pointer.
  std::vector<std::shared_ptr<Equipable>> weapons_inventory_;
  std::vector<std::shared_ptr<InventoryItem>> items_inventory_;

  bool equipped_;
};

UnitAttribute operator|(UnitAttribute a, UnitAttribute b);

} // namespace srpg

#endif //SRPG_ENGINE_UNIT_H
