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
        repetitions = delayMs = 0;
}

/****************************************************************************/

AbstractTween::State AbstractTween::transition (State s)
{
	switch (s) {
	case INIT:
		if (state == DELAY) {
			state = INIT;
			delayExit ();
			initEntry ();
		}
		break;

	case DELAY:
		if (state == INIT ) {
			state = DELAY;
			initExit ();
			delayEntry ();
		}

		else if (state == RUN) {
			state = DELAY;
			runExit ();
			delayEntry ();
		}

		break;

	case RUN:
		if (state == INIT) {
			state = RUN;
			initExit ();
			runEntry ();
		}
		else if (state == RUN) {
			runExit ();
			runEntry ();
		}
		else if (state == DELAY) {
			state = RUN;
			delayExit ();
			runEntry ();
		}
		else if (state == FINISHED) {
			state = RUN;
			finishedExit ();
			runEntry ();
		}
		break;

	case FINISHED:
		if (state == RUN) {
			state = FINISHED;
			runExit ();
			finishedEntry ();
		}
		break;

	default:
		break;
	}

	return state;
}

} /* namespace Tween */
