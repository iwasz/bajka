/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TESTEVENT_H_
#define TESTEVENT_H_

#include "IEvent.h"

class TestEvent : public Event::AbstractEvent {
public:
        virtual ~TestEvent () {}
};

#	endif /* TESTEVENT_H_ */
