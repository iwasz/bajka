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

//void AbstractTween::clear ()
//{
//        state = INIT;
//        yoyo = false;
//        currentMs = repetitions = delayMs = 0;
//}

/****************************************************************************/

void AbstractTween::update (int deltaMs, bool reverse)
{
        if (state == END) {
                return;
        }
        else if (state == FINISHED) {
                if (!reverse) {
                        transition (END, reverse);
                        return;
                }

                transition (RUN, reverse);
                update (deltaMs, reverse);
        }
        else if (state == INIT) {
                if (reverse) {
                        transition (END, reverse);
                        return;
                }

                transition(((delayMs) ? (DELAY) : (RUN)), reverse);
                update (deltaMs, reverse);
        }
        else if (state == DELAY) {
                currentMs += deltaMs;
                int remainingMs = currentMs - delayMs;

                if (remainingMs >= 0) {
                        transition ((((reverse)) ? (INIT) : (RUN)), reverse);
                }

                if (remainingMs > 0) {
                        update (remainingMs, reverse);
                }
        }
        else if (state == RUN) {

                bool direction = forward ^ reverse;

                updateRun (deltaMs, direction);

                if (checkEnd (direction)) {

                        if (!currentRepetition) {
                                transition (((reverse) ? (DELAY) : (FINISHED)), reverse);
                        }
                        else {
                                --currentRepetition;

                                if (yoyo) {
                                        forward = !forward;
                                }

                                transition (RUN, reverse);
                        }
                }
        }
}

/****************************************************************************/

AbstractTween::State AbstractTween::transition (State s, bool reverse)
{
	switch (s) {
	case INIT:
                if (state == DELAY) {
			delayExit (reverse);
			initEntry (reverse);
		}
                state = INIT;
		break;

	case DELAY:
                if (state == INIT ) {
                        currentRepetition = repetitions;
			initExit (reverse);
			delayEntry (reverse);
		}

		else if (state == RUN) {
			runExit (reverse);
			delayEntry (reverse);
		}
                state = DELAY;
		break;

	case RUN:
                if (state == INIT) {
                        currentRepetition = repetitions;
			initExit (reverse);
			runEntry (reverse);
		}
		else if (state == RUN) {
			runExit (reverse);
			runEntry (reverse);
		}
		else if (state == DELAY) {
			delayExit (reverse);
			runEntry (reverse);
		}
		else if (state == FINISHED) {
		        currentRepetition = repetitions;
			finishedExit (reverse);
			runEntry (reverse);
		}
                state = RUN;
		break;

	case FINISHED:
                if (state == RUN) {
			runExit (reverse);
			finishedEntry (reverse);
		}
                state = FINISHED;
		break;

        case END:
                state = END;
                break;

	default:
		break;
	}

	return state;
}

} /* namespace Tween */
