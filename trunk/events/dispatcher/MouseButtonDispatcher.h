/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 18, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MOUSEBUTTONDISPATCHER_H_
#define MOUSEBUTTONDISPATCHER_H_

#include "IEvent.h"
#include "MouseButtonEvent.h"

namespace Events {

class MouseButtonDispatcher : public AbstractObservable <MouseButtonEvent> {
public:

        virtual ~MouseButtonDispatcher () {}

        virtual void notifyObservers (const IEvent &event);

private:

//        bool selectedButton;
//        MouseButton button;
//        allowedButtons
//        allowedTypes
//        regions

};

}

#	endif /* MOUSEBUTTONDISPATCHER_H_ */
