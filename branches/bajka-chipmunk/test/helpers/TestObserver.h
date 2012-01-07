/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TESTOBSERVER_H_
#define TESTOBSERVER_H_

#include "TestEvent.h"

struct TestObserver : public Event::IObserver {

        TestObserver () : eventCount (0) {}
        virtual ~TestObserver () {}

        virtual void onEvent (const TestEvent &event)
        {
                eventCount++;
        }

        int eventCount;
};

#	endif /* TESTOBSERVER_H_ */
