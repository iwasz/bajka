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
#include "MouseButtonDispatcher.h"

namespace Events {

void MouseButtonDispatcher::notifyObservers (const IEvent &event)
{
        std::cerr << "Hello world" << std::endl;
}

}
