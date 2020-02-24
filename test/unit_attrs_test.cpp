//
// Created by matthew on 1/26/20.
//

#include <boost/test/unit_test.hpp>
#include "unit_attrs.hh"

using namespace srpg;

BOOST_AUTO_TEST_SUITE(unit_attrs)

BOOST_AUTO_TEST_CASE(core_stat_operators) {
    CoreStatSpread a(1, 2, 1, 2, 1, 2, 1);
    CoreStatSpread b(2, 1, 2, 1, 2, 1, 2);

    BOOST_CHECK((a + b) == CoreStatSpread(3, 3, 3, 3, 3, 3, 3));
    BOOST_CHECK((a + b + a) == CoreStatSpread(4, 5, 4, 5, 4, 5, 4));
}

BOOST_AUTO_TEST_SUITE_END()
