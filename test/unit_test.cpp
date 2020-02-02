//
// Created by matthew on 1/11/20.
//

#include <boost/test/unit_test.hpp>
#include "unit.h"
#include "weapon.h"

using namespace srpg;

struct Globals {
  Globals()
    : mercenary(CoreStatSpread(), MovementType::Infantry, UnitAttribute::None, WeaponType::Sword),
      myrmidon(myrmidon_bonuses, MovementType::Infantry, UnitAttribute::None, WeaponType::Sword),
      potion(CoreStatSpread(), [](Unit& u) {u.offset_hp(10); }) {
    myrmidon_bonuses = CoreStatSpread(3, 2, 1, 0, 1, 2, 3);
    merc_bases = CoreStatSpread(20, 7, 4, 0, 0, 5, 9);
  }

  CoreStatSpread myrmidon_bonuses;
  CoreStatSpread merc_bases;
  UnitClass mercenary;
  UnitClass myrmidon;
  InventoryItem potion;
};

BOOST_FIXTURE_TEST_SUITE(unit, Globals)

BOOST_AUTO_TEST_CASE(attributes) {
  Unit x(merc_bases, CoreStatSpread(), UnitAttribute::Draconic | UnitAttribute::Winged, mercenary, 2);

  BOOST_CHECK(x.has_attributes(UnitAttribute::Draconic));
  BOOST_CHECK(x.has_attributes(UnitAttribute::Winged));
  BOOST_CHECK(x.has_attributes(UnitAttribute::Draconic | UnitAttribute::Winged));

  BOOST_CHECK(! x.has_attributes(UnitAttribute::Beastial));
  BOOST_CHECK(! x.has_attributes(UnitAttribute::Armored));
  BOOST_CHECK(! x.has_attributes(UnitAttribute::Draconic | UnitAttribute::Beastial));
}

BOOST_AUTO_TEST_CASE(null_attributes) {
  Unit x(merc_bases, CoreStatSpread(), UnitAttribute::None, mercenary, 4);

  BOOST_CHECK(x.has_attributes(UnitAttribute::None));

  BOOST_CHECK(! x.has_attributes(UnitAttribute::Draconic));
  BOOST_CHECK(! x.has_attributes(UnitAttribute::Winged));
  BOOST_CHECK(! x.has_attributes(UnitAttribute::Beastial));
  BOOST_CHECK(! x.has_attributes(UnitAttribute::Armored));
}

BOOST_AUTO_TEST_CASE(stat_minimums) {
  Unit x(CoreStatSpread(10, 10, 10, 10, 10, 10, 10), CoreStatSpread(), UnitAttribute::Winged, mercenary, 11);
  x.buff(CoreStatSpread(-255, -255, -255, -255, -255, -255, -255));

  BOOST_CHECK(CoreStatSpread(1, 0, 0, 0, 0, 0, 0) == x.stats());
}

BOOST_AUTO_TEST_CASE(stat_buffing) {
  Unit x(CoreStatSpread(10, 10, 10, 10, 10, 10, 10), CoreStatSpread(), UnitAttribute::Winged, mercenary, 11);
  x.buff(CoreStatSpread(5, 5, 5, 5, 5, 5, 5));

  BOOST_CHECK(CoreStatSpread(15, 15, 15, 15, 15, 15, 15) == x.stats());
}

BOOST_AUTO_TEST_CASE(hp_reduction) {
  Unit x(merc_bases, CoreStatSpread(), UnitAttribute::None, mercenary, 4);

  BOOST_CHECK(merc_bases.hp == x.remaining_hp());

  x.offset_hp(-6);

  BOOST_CHECK_EQUAL(merc_bases.hp, x.stats().hp);
  BOOST_CHECK_EQUAL(merc_bases.hp - 6, x.remaining_hp());
}

BOOST_AUTO_TEST_CASE(hp_restoration) {
  Unit x(merc_bases, CoreStatSpread(), UnitAttribute::None, mercenary, 4);

  BOOST_CHECK_EQUAL(merc_bases.hp, x.remaining_hp());

  x.offset_hp(12);

  BOOST_CHECK_EQUAL(merc_bases.hp, x.stats().hp);
  BOOST_CHECK_EQUAL(merc_bases.hp, x.remaining_hp());

  x.offset_hp(-6);
  x.offset_hp(4);

  BOOST_CHECK(merc_bases.hp == x.stats().hp);
  BOOST_CHECK(merc_bases.hp - 2 == x.remaining_hp());
}

BOOST_AUTO_TEST_CASE(no_item_by_default) {
  Unit x(merc_bases, CoreStatSpread(), UnitAttribute::None, mercenary, 4);

  BOOST_CHECK(nullptr == x.held_item());
}

BOOST_AUTO_TEST_CASE(granting_an_item) {
  Unit x(merc_bases, CoreStatSpread(), UnitAttribute::None, mercenary, 4);
  x.give_item(potion);

  // Both f and potion should be invalid.
  BOOST_REQUIRE(nullptr != x.held_item());

  // As a result, the result must be checked independently.
  x.offset_hp(-15);

  x.held_item()->on_use(x);

  // I could check for reduced durability here, but have decided to put that off with related tests.

  BOOST_CHECK(merc_bases.hp - 5 == x.remaining_hp());
}

BOOST_AUTO_TEST_CASE(autoleveling) {
  Unit x(merc_bases, CoreStatSpread(90, 45, 50, 50, 45, 50, 50), UnitAttribute::None, mercenary, 8);

  BOOST_CHECK_EQUAL(1, x.level());
  BOOST_CHECK_EQUAL(0, x.exp());

  bool failed = false;
  x.give_exp(EXP_PER_LEVEL, failed);

  BOOST_REQUIRE(! failed);
  BOOST_CHECK_EQUAL(2, x.level());

  // No growths are high enough to level anything yet.
  BOOST_CHECK(merc_bases == x.stats());

  x.give_exp(EXP_PER_LEVEL, failed);
  BOOST_REQUIRE(! failed);
  BOOST_CHECK_EQUAL(3, x.level());

  BOOST_CHECK(merc_bases + CoreStatSpread(1, 0, 1, 1, 0, 1, 1) == x.stats());
}

BOOST_AUTO_TEST_CASE(unequipped_by_default) {
  Unit x(merc_bases, CoreStatSpread(90, 45, 50, 50, 45, 50, 50), UnitAttribute::None, mercenary, 8);

  BOOST_CHECK(! x.is_equipped());
  BOOST_CHECK(nullptr == x.held_item());
}

BOOST_AUTO_TEST_CASE(equip_fails_when_item_not_present) {
  Unit x(merc_bases, CoreStatSpread(), UnitAttribute::None, mercenary, 8);

  BOOST_REQUIRE(nullptr == x.held_item());

  BOOST_CHECK(! x.equip());
  BOOST_REQUIRE(nullptr == x.held_item());
}

BOOST_AUTO_TEST_CASE(equipping_a_non_equippable_item_fails) {
  Unit x(merc_bases, CoreStatSpread(), UnitAttribute::None, mercenary, 8);

  // Note that the potion is not an equipable item, although it may be held and used.
  x.give_item(potion);

  // Ensure that it doesn't equip on a give operation.
  BOOST_CHECK(nullptr == x.equipped_weapon());

  // Ensure that the item may not be manually equipped.
  BOOST_CHECK(! x.equip());

  BOOST_CHECK(nullptr == x.equipped_weapon());

  BOOST_REQUIRE(nullptr != x.held_item());
}

BOOST_AUTO_TEST_CASE(able_to_equip_an_eqiupable_item) {
  Unit x(merc_bases, CoreStatSpread(), UnitAttribute::None, mercenary, 8);
  Weapon w(WeaponType::Sword, UnitAttribute::None, 1, 1, 1, 1, 1, false);

  x.give_item(w);

  BOOST_CHECK(nullptr != x.held_item());
  BOOST_CHECK(nullptr == x.equipped_weapon());
  BOOST_CHECK(!x.is_equipped());
  BOOST_CHECK(x.equip());
  BOOST_CHECK(x.is_equipped());
}

// TODO(matthew-c21): Add tests for units being (un)able to equip weapons of certain ranks or type based on class.

BOOST_AUTO_TEST_CASE(units_die_at_zero_hp) {
  Unit x(merc_bases, CoreStatSpread(), UnitAttribute::None, mercenary, 8);

  BOOST_REQUIRE(! x.dead());

  x.offset_hp(-merc_bases.hp / 2);

  BOOST_CHECK(! x.dead());

  x.offset_hp(-merc_bases.hp / 2 + 1);

  BOOST_CHECK(x.dead());
}

BOOST_AUTO_TEST_CASE(stats_correct_after_class_bonus) {
  Unit merc1(CoreStatSpread(20, 7, 4, 0, 0, 5, 9), CoreStatSpread(), UnitAttribute::None, mercenary, 3);
  Unit merc2(merc_bases, CoreStatSpread(), UnitAttribute::None, myrmidon, 3);

  BOOST_CHECK(merc_bases == merc1.stats());
  BOOST_CHECK(merc_bases + myrmidon_bonuses == merc2.stats());
}

BOOST_AUTO_TEST_SUITE_END()
