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
#include "../../controller/SimpleController.h"

namespace Service {

/**
 * W połączeniu z ParalaxModel i ScrollMarginController stanowi implementację
 * scrollowania ekranu.
 */
class ScrollController : public Controller::SimpleController {
public:
        __c (void)
        _b ("SimpleController")

        ScrollController () :
                onDown (this, "/scroll/down", "$down (%0)"),
                onUp (this, "/scroll/up", "$up (%0)"),
                onRight (this, "/scroll/right", "$right (%0)"),
                onLeft (this, "/scroll/left", "$left (%0)")
                {}

        virtual ~ScrollController () {}

        _m (down)
        void down (double speed);

        _m (up)
        void up (double speed);

        _m (left)
        void left (double speed);

        _m (right)
        void right (double speed);

//        TODO
//        void move (const Distance &d);

        virtual bool onTimer (Event::TimerEvent *e);

private:

        Signal::Listener onDown, onUp, onLeft, onRight;
        Geometry::Point currentMove;

        _e (ScrollController)
};

}

#	endif /* SCROLLSERVICE_H_ */