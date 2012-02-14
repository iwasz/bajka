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

//void AbstractTween::rewind ()
//{
//        finished = started = false;
//}

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

		else if (state == FORWARD) {
			state = DELAY;
			forwardExit ();
			delayEntry ();
		}

		break;

	case FORWARD:
		if (state == INIT) {
			state = FORWARD;
			initExit ();
			forwardEntry ();
		}
		else if (state == FORWARD) {
			forwardExit ();
			forwardEntry ();
		}
		else if (state == DELAY) {
			state = FORWARD;
			delayExit ();
			forwardEntry ();
		}
		else if (state == BACKWARD) {
			state = FORWARD;
			forwardExit ();
			forwardEntry ();
		}
		else if (state == FINISHED) {
			state = FORWARD;
			finishedExit ();
			forwardEntry ();
		}
		break;

	case BACKWARD:
		if (state == FORWARD) {
			state = BACKWARD;
			forwardExit ();
			backwardEntry ();
		}
		else if (state == FINISHED) {
			state = BACKWARD;
			finishedExit ();
			backwardEntry ();
		}
		break;

	case FINISHED:
		if (state == FORWARD) {
			state = FINISHED;
			forwardExit ();
			finishedEntry ();
		}
		else if (state == BACKWARD) {
			state = FINISHED;
			backwardExit ();
			finishedEntry ();
		}
		break;

	default:
		break;
	}

	return state;
}

} /* namespace Tween */
