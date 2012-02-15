/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AtomicTween.h"
#include "Manager.h"

namespace Tween {

void AtomicTween::Target::clear ()
{
    accessor = NULL;
    tween = NULL;
    startValue = 0;
    endValue = 0;
    absolute = true;
}

/****************************************************************************/

void AtomicTween::Target::init ()
{
	assertThrow (accessor, "AtomicTween::init : !accessor");
	startValue = accessor->getValue (tween->object);
}

/****************************************************************************/

void AtomicTween::Target::update ()
{
        double deltaValue = endValue - ((absolute) ? (startValue) : (0));
        double comuted = tween->equation->compute (tween->currentMs, startValue, deltaValue, tween->durationMs);
        accessor->setValue (tween->object, comuted);
}

/*##########################################################################*/

AtomicTween *to (void *targetObject, unsigned int durationMs, Ease ease)
{
        AtomicTween *tween = AtomicTween::create ();
        tween->equation = Manager::getMain ()->getEase (ease);
        tween->durationMs = durationMs;
        tween->object = targetObject;
        return tween;
}

/****************************************************************************/

AtomicTween *AtomicTween::create ()
{
        // TODO pula.
        return new AtomicTween;
}

/****************************************************************************/

void AtomicTween::clear ()
{
	AbstractTween::clear ();

        equation = NULL;
        durationMs = 0;
        currentMs = 0;
        object = NULL;
        targets.clear ();
}

/****************************************************************************/

void AtomicTween::initEntry () {}
void AtomicTween::initExit ()
{
	currentRepetition = repetitions;
        currentMs = ((currentDirection) ? (0) : (durationMs));

	for (TargetVector::iterator i = targets.begin (); i != targets.end (); ++i) {
		(*i)->init ();
	}

}
void AtomicTween::delayEntry () {}
void AtomicTween::delayExit ()
{
}
void AtomicTween::forwardEntry ()
{
	currentMs = ((currentDirection) ? (0) : (durationMs));
}
void AtomicTween::forwardExit () {}
void AtomicTween::backwardEntry () {}
void AtomicTween::backwardExit () {}
void AtomicTween::finishedEntry  () {}
void AtomicTween::finishedExit ()
{
	currentRepetition = repetitions;
}

/****************************************************************************/

void AtomicTween::update (int deltaMs)
{
        if (state == FINISHED) {
                return;
        }
        else if (state == INIT) {

                if (delayMs) {
                        transition(DELAY);
                }
                else {
                        transition (RUN);
                }

                update (deltaMs); // Żeby nie stracić iteracji.
        }
        else if (state == DELAY) {
                currentMs += deltaMs;
                int remainingMs = currentMs - delayMs;

                if (remainingMs >= 0) {
                        transition (RUN);
                }

                if (remainingMs > 0) {
                        update(remainingMs);
                }
        }
        else if (state == RUN) {

                if (currentDirection) {
                        currentMs += deltaMs;

                        if (currentMs > durationMs) {
                                currentMs = durationMs;
                        }
                }
                else {
                        currentMs -= deltaMs;

                        if (currentMs < 0) {
                                currentMs = 0;
                        }
                }

                for (TargetVector::iterator i = targets.begin();
                                i != targets.end(); ++i) {
                        (*i)->update ();
                }

                if ((currentDirection && currentMs >= durationMs) || (!currentDirection && currentMs <= 0)) {
                        if (!currentRepetition) {
                                transition(FINISHED);
                        }
                        else {
                                --currentRepetition;

                                if (yoyo) {
                                        currentDirection = !currentDirection;
                                }

                                transition (RUN);
                        }
                }
        }
}

/****************************************************************************/

AtomicTween *AtomicTween::target (unsigned int property, double value, bool abs)
{
        Target *target = Target::create ();
        target->accessor = Manager::getMain ()->getAccessor (property);
        target->endValue = value;
        target->absolute = abs;
        target->tween = this;
        targets.push_back (target);
        return this;
}

} /* namespace Tween */
