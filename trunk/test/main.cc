/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "EventsTest.h"
#include "UtilTest.h"

int main (int argc, char **argv)
{
        EventsTest::testSimpleObserver ();
        UtilTest::testNextPowerOfTwo ();

        return 0;
}
