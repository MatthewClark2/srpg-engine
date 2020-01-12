//
// Created by matthew on 1/11/20.
//

#define BOOST_TEST_MODULE Unit
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>
#include "unit.h"

BOOST_AUTO_TEST_CASE(BitwiseEnum) {
    auto greatKnight = MovementType::Armored | MovementType::Cavalry;
    BOOST_CHECK(greatKnight == MovementType::Armored);
    BOOST_CHECK(greatKnight == MovementType::Cavalry);

    BOOST_CHECK(greatKnight != MovementType::Infantry);
    BOOST_CHECK(greatKnight != MovementType::Flying);
    BOOST_CHECK(greatKnight != MovementType::Brigand);
}
