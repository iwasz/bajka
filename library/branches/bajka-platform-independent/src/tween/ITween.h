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

class ITween {
public:
        virtual ~ITween () {}
        virtual void update (int deltaMs, bool reverse) = 0;

        enum State { INIT, DELAY, RUN, FINISHED, END };
        virtual State getState () const = 0;

        virtual void start (Manager *m = NULL) = 0;

        virtual ITween *repeat (unsigned int num, bool yoyo = false) = 0;
        virtual ITween *delay (unsigned int duration) = 0;

        virtual int getDurationMs () const = 0;
        virtual void setDurationMs (int ms) = 0;
};

typedef std::list <ITween *> TweenList;

} /* namespace Tween */

#	endif /* ITWEEN_H_ */
