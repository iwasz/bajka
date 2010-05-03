/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 22, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <cassert>

#include "UtilTest.h"
#include "Util.h"

void UtilTest::testNextPowerOfTwo ()
{
        assert (Util::Math::nextSqr (1) == 1);
        assert (Util::Math::nextSqr (2) == 2);
        assert (Util::Math::nextSqr (3) == 4);
        assert (Util::Math::nextSqr (5) == 8);
        assert (Util::Math::nextSqr (9) == 16);
        assert (Util::Math::nextSqr (1000) == 1024);
        assert (Util::Math::nextSqr (1024) == 1024);

        std::cerr << "OK UtilTest::testNextPowerOfTwo" << std::endl;
}
