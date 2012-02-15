/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractTween.h"
#include "Manager.h"

namespace Tween {

void AbstractTween::start (Manager *m)
{
        if (m) {
                m->setTween (this);
        }
        else {
                Manager::getMain ()->setTween (this);
        }
}

/****************************************************************************/

void AbstractTween::clear ()
{
        state = INIT;
        yoyo = false;
        currentMs = repetitions = delayMs = 0;
}

/****************************************************************************/

AbstractTween::State AbstractTween::transition (State s)
{
	switch (s) {
	case INIT:
                if (state == DELAY) {
			delayExit ();
			initEntry ();
		}
                state = INIT;
		break;

	case DELAY:
                if (state == INIT ) {
			initExit ();
			delayEntry ();
		}

		else if (state == RUN) {
			runExit ();
			delayEntry ();
		}
                state = DELAY;
		break;

	case RUN:
                if (state == INIT) {
			initExit ();
			runEntry ();
		}
		else if (state == RUN) {
			runExit ();
			runEntry ();
		}
		else if (state == DELAY) {
			delayExit ();
			runEntry ();
		}
		else if (state == FINISHED) {
			finishedExit ();
			runEntry ();
		}
                state = RUN;
		break;

	case FINISHED:
                if (state == RUN) {
			runExit ();
			finishedEntry ();
		}
                state = FINISHED;
		break;

	default:
		break;
	}

	return state;
}

} /* namespace Tween */
