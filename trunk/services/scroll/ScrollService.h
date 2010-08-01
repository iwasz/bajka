/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SCROLLSERVICE_H_
#define SCROLLSERVICE_H_

#include <Signal.h>
#include <Reflection.h>

namespace Service {

class ScrollService {
public:
        __c (void)

        ScrollService () : onDown (this, "/a/down", "$down()") {}
        virtual ~ScrollService () {}

        _m (down) void down (/*double speed*/);
        void up (double speed);
        void left (double speed);
        void right (double speed);

//        void move (const Distance &d);
private:

        Signal::Listener onDown/*, onUp, onLeft, onRight*/;

        _e (ScrollService)
};

}

#	endif /* SCROLLSERVICE_H_ */
