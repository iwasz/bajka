/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_SDL
#ifndef TIMERDISPATCHER_H_
#define TIMERDISPATCHER_H_

#include "ReflectionMacros.h"
#include "types/TimerEvent.h"
#include "IDispatcher.h"

namespace Event {

/**
 * Generuje eventy zegarowe używając do tego timerów SDL.
 * \ingroup Events
 */
class TimerDispatcher : public Event::IDispatcher {
public:
        C__ (void)

        TimerDispatcher () : tickInterval (30), prevTime (0), app (NULL) {}
        virtual ~TimerDispatcher () {}

        void run (Model::IModel *m, Event::EventIndex const &modeliIndex, Event::PointerInsideIndex *pointerInsideIndex);
        void reset () {}

/*--------------------------------------------------------------------------*/

        unsigned int getTickInterval () const { return tickInterval; }
        m_ (setTickInterval) void setTickInterval (unsigned int tickInterval) { this->tickInterval = tickInterval; }

        Util::App *getApp () { return app; }
        void setApp (Util::App *a) { app = a; }

private:

        unsigned int tickInterval;
        unsigned int prevTime;
        Event::TimerEvent timerEvent;
        Util::App *app;

        E_ (TimerDispatcher)
};

}

#endif /* TIMERDISPATCHER_H_ */
#endif
