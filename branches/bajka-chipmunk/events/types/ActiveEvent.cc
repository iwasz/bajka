/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ActiveEvent.h"

namespace Event {

std::string ActiveEvent::toString () const
{
       std::string ret = std::string ("ActiveEvent (active=") + ((active) ? ("true") : ("false")) +
                       ", state=";

       switch (state) {
       case MOUSE:
               ret += "MOUSE";
               break;

       case KEYBOARD:
               ret += "KEYBOARD";
               break;

       case WINDOW:
               ret += "WINDOW";
               break;

       default:
               ret += "?";
               break;
       }

       ret += ")";
       return ret;
}

} /* namespace Event */
