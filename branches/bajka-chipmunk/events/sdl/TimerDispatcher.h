/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TIMERDISPATCHER_H_
#define TIMERDISPATCHER_H_

#include "ReflectionMacros.h"
#include "types/TimerEvent.h"
#include "IDispatcher.h"

namespace Sdl {

/**
 * Generuje eventy zegarowe używając do tego timerów SDL.
 * \ingroup Events
 */
class TimerDispatcher : public Event::IDispatcher {
public:
        C__ (void)

        TimerDispatcher () : tickInterval (30), prevTime (0)/*, observer (NULL)*/ {}
        virtual ~TimerDispatcher () {}

        void run (Model::IModel *m, Event::ModelIndex const &modeliIndex);

/*--------------------------------------------------------------------------*/

        unsigned int getTickInterval () const { return tickInterval; }
        m_ (setTickInterval) void setTickInterval (unsigned int tickInterval) { this->tickInterval = tickInterval; }

private:

        unsigned int tickInterval;
        unsigned int prevTime;
        Event::TimerEvent timerEvent;

        E_ (TimerDispatcher)
};

}

#	endif /* TIMERDISPATCHER_H_ */
