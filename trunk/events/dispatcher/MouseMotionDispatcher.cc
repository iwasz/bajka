/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 19, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>

#include "MouseMotionDispatcher.h"
#include "InclusionService.h"
#include "MouseMotionEvent.h"

namespace Events {

void MouseMotionDispatcher::update (const IObservable <MouseMotionEvent> &observable,
                                    const MouseMotionEvent &event)
{
        bool inside = Util::InclusionService::include (area, event.getPosition ());

        if ((mode == IN && !inside) || (mode == OUT && inside)) {
                return;
        }

        std::cerr << "Mouse over : " << event.getPosition () << std::endl;

        notifyObservers (event);
}

} // nam
