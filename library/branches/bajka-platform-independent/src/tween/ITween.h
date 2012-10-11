/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_TWEEN_ITWEEN_H_
#define BAJKA_TWEEN_ITWEEN_H_

#include <list>
#include <cstddef>

namespace Tween {
class Manager;
class TweeningProperty;
class IMultiTween;

class ITween {
public:
        virtual ~ITween () {}
        virtual void update (int deltaMs, bool reverse) = 0;

        enum State { INIT, DELAY, RUN, FINISHED, END };
        virtual State getState () const = 0;

        virtual void start () = 0;

        virtual ITween *repeat (unsigned int num, bool yoyo = false) = 0;
        virtual ITween *delay (unsigned int duration) = 0;

        virtual int getDurationMs () const = 0;
        virtual void setDurationMs (int ms) = 0;

        virtual void remove (void const *target, bool onlyActive = false) = 0;
        virtual void remove (void const *target, TweeningProperty *property, bool onlyActive = false) = 0;

        virtual void setParent (IMultiTween *p) = 0;
};

typedef std::list <ITween *> TweenList;

} /* namespace Tween */

#	endif /* ITWEEN_H_ */
