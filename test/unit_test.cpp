//
// Created by matthew on 1/11/20.
//

#include <boost/test/unit_test.hpp>
#include "unit.h"
#include "weapon.h"

using namespace srpg;

BOOST_AUTO_TEST_SUITE(unit)

BOOST_AUTO_TEST_CASE(stats_correct_after_class_bonus) {
  CoreStatSpread myrmidon_bonuses(3, 2, 1, 0, 1, 2, 3);
  CoreStatSpread merc_bases(20, 7, 4, 0, 0, 5, 9);

  // It would be nice if C++ had default partial constructors, but that may be worth adding later.
  UnitClass mercenary(CoreStatSpread(), MovementType::Infantry, UnitAttribute::None, WeaponType::Sword);
  UnitClass myrmidon(myrmidon_bonuses, MovementType::Infantry, UnitAttribute::None, WeaponType::Sword);

  Unit merc1(CoreStatSpread(20, 7, 4, 0, 0, 5, 9), CoreStatSpread(), UnitAttribute::None, mercenary, 3);
  Unit merc2(merc_bases, CoreStatSpread(), UnitAttribute::None, myrmidon, 3);

  BOOST_CHECK(merc_bases == merc1.stats());
  BOOST_CHECK(merc_bases + myrmidon_bonuses == merc2.stats());
}

BOOST_AUTO_TEST_SUITE_END()
