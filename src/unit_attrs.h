//
// Created by matthew on 1/26/20.
//

#ifndef SRPG_ENGINE_UNIT_ATTRS_H
#define SRPG_ENGINE_UNIT_ATTRS_H

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

  /**
   * Default 0 constructor.
   */
  CoreStatSpread() : CoreStatSpread(0, 0, 0, 0, 0, 0, 0) {}

  CoreStatSpread(int hp, int atk, int def, int res, int luk, int skl, int spd)
      : hp(hp), atk(atk), def(def), res(res), luk(luk), skl(skl), spd(spd) {}

  friend CoreStatSpread operator==(const CoreStatSpread& lhs, const CoreStatSpread&& rhs);
  friend CoreStatSpread operator+(const CoreStatSpread& lhs, const CoreStatSpread&& rhs);
};

UnitAttribute operator|(UnitAttribute a, UnitAttribute b);

#endif //SRPG_ENGINE_UNIT_ATTRS_H
