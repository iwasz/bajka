/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <Object.h>
#include "IEvent.h"

namespace Event {

/**
 *
 */
struct IObserver : public Core::Object {

        virtual ~IObserver () {}
        virtual void onEvent (const IEvent &event) = 0;

};

}

#	endif /* OBSERVER_H_ */
