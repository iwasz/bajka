/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <Pointer.h>
#include <assert.h>

#include "EventsTest.h"
#include "Events.h"

#include "helpers/TestObserver.h"
#include "helpers/TestObservable.h"
#include "helpers/TestEvent.h"

/**
 * Testuje w najprostszy sposób strukturę Observer - Observable.
 */
void EventsTest::testSimpleObserver ()
{
        TestObservable mouse;

        Ptr <TestObserver> sprite1 (new TestObserver);
        Ptr <TestObserver> sprite2 (new TestObserver);

        mouse.addObserver (sprite1);

        assert (sprite1->eventCount == 0);
        assert (sprite2->eventCount == 0);

        mouse.notifyObservers (TestEvent ());
        assert (sprite1->eventCount == 1);

        mouse.notifyObservers (TestEvent ());
        assert (sprite1->eventCount == 2);

        mouse.addObserver (sprite2);

        mouse.notifyObservers (TestEvent ());
        assert (sprite1->eventCount == 3);
        assert (sprite2->eventCount == 1);

        mouse.notifyObservers (TestEvent ());
        assert (sprite1->eventCount == 4);
        assert (sprite2->eventCount == 2);

        std::cerr << "OK EventsTest::testSimpleObserver" << std::endl;
}
