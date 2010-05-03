/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TESTEVENT_H_
#define TESTEVENT_H_

#include "IEvent.h"

class TestEvent : public Events::IEvent {
public:
        virtual ~TestEvent () {}
};

#	endif /* TESTEVENT_H_ */
