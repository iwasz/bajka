#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cassert>

#include "Util.h"

BOOST_AUTO_TEST_SUITE (UtilTest);
 
BOOST_AUTO_TEST_CASE (testBasic)
{
        BOOST_CHECK (Util::Math::nextSqr (1) == 1);
        BOOST_CHECK (Util::Math::nextSqr (2) == 2);
        BOOST_CHECK (Util::Math::nextSqr (3) == 4);
        BOOST_CHECK (Util::Math::nextSqr (5) == 8);
        BOOST_CHECK (Util::Math::nextSqr (9) == 16);
        BOOST_CHECK (Util::Math::nextSqr (1000) == 1024);
        BOOST_CHECK (Util::Math::nextSqr (1024) == 1024);
}
 
BOOST_AUTO_TEST_SUITE_END ();
