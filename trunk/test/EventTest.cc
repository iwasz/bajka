#define BOOST_TEST_MODULE ExampleTest
#define BOOST_TEST_DYN_LINK
 
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <Pointer.h>

#include "Events.h"

#include "helpers/TestObserver.h"
#include "helpers/TestObservable.h"
#include "helpers/TestEvent.h"

BOOST_AUTO_TEST_SUITE (EventTest);

/**
 * Testuje w najprostszy sposób strukturę Observer - Observable.
 */
BOOST_AUTO_TEST_CASE (testBasic)
{
        TestObservable mouse;

        Ptr <TestObserver> sprite1 (new TestObserver);
        Ptr <TestObserver> sprite2 (new TestObserver);

        mouse.addObserver (sprite1);

        BOOST_CHECK (sprite1->eventCount == 0);
        BOOST_CHECK (sprite2->eventCount == 0);

        mouse.notifyObservers (TestEvent ());
        BOOST_CHECK (sprite1->eventCount == 1);

        mouse.notifyObservers (TestEvent ());
        BOOST_CHECK (sprite1->eventCount == 2);

        mouse.addObserver (sprite2);

        mouse.notifyObservers (TestEvent ());
        BOOST_CHECK (sprite1->eventCount == 3);
        BOOST_CHECK (sprite2->eventCount == 1);

        mouse.notifyObservers (TestEvent ());
        BOOST_CHECK (sprite1->eventCount == 4);
        BOOST_CHECK (sprite2->eventCount == 2);
}
 
BOOST_AUTO_TEST_SUITE_END ();
