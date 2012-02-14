/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_TWEEN_ITWEEN_H_
#define BAJKA_TWEEN_ITWEEN_H_

#include <vector>
#include <list>
#include <cstddef>

namespace Tween {
class Manager;

class ITween {
public:
        virtual ~ITween () {}
        virtual void update (int deltaMs) = 0;

        enum State { INIT, DELAY, FORWARD, BACKWARD, FINISHED };
        virtual State getState () const = 0;


//        virtual bool getFinished () const = 0;
//        virtual bool getStarted () const = 0;
        virtual void start (Manager *m = NULL) = 0;

        virtual ITween *repeat (unsigned int num, bool yoyo = false) = 0;
        virtual ITween *delay (unsigned int duration) = 0;

        /**
         * Czyści, tak, żeby można było użyc tego tweena ponownie z innymi parametrami.
         */
        virtual void clear () = 0;

        /**
         * Przewija do początku.
         */
//        virtual void rewind () = 0;
};

typedef std::vector <ITween *> TweenVector;
typedef std::list <ITween *> TweenList;

} /* namespace Tween */

#	endif /* ITWEEN_H_ */
