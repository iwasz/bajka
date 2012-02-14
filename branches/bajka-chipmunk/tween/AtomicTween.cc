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

//void AtomicTween::init ()
//{
//}

/****************************************************************************/

void AtomicTween::clear ()
{
	AbstractTween::clear ();

    equation = NULL;
    accessor = NULL;
    linked = NULL;
    durationMs = 0;
    currentMs = 0;
    startValue = 0;
    targetValue = 0;
    object = NULL;
    absolute = false;
    tweens.release ();
}

/****************************************************************************/

void AtomicTween::initEntry () {}
void AtomicTween::initExit ()
{
	currentRepetition = repetitions;
	assertThrow (accessor, "AtomicTween::init : !accessor");
	startValue = accessor->getValue (object);
	currentMs = 0;
}
void AtomicTween::delayEntry () {}
void AtomicTween::delayExit ()
{
}
void AtomicTween::forwardEntry ()
{
	currentMs = 0;
	assertThrow (accessor, "AtomicTween::init : !accessor");
	accessor->setValue (object, startValue);

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
                        transition (DELAY);
                }
                else {
                        transition (FORWARD);
                }

                update (deltaMs); // Żeby nie stracić iteracji.
        }
        else if (state == DELAY) {
                if (!linked) {
                        currentMs += deltaMs;
                }

                int remainingMs = getCurMs () - delayMs;
                if (remainingMs >= 0) {
                        transition (FORWARD);
                }

                if (remainingMs > 0) {
                        update (remainingMs);
                }
        }
	else if (state == FORWARD) {
	        if (!linked) {
	                currentMs += deltaMs;

	                if (currentMs > durationMs) {
	                        currentMs = durationMs;
	                }
	        }

                double deltaValue = targetValue - ((absolute) ? (startValue) : (0));
                double comuted = equation->compute (getCurMs (), startValue, deltaValue, durationMs);
                accessor->setValue (object, comuted);
                bool notFinished = getCurMs () < durationMs;

                if (tweens.get ()) {
                        for (TweenVector::iterator i = tweens->begin (); i != tweens->end (); ++i) {
                                (*i)->update (deltaMs);
                                notFinished |= (*i)->getState () != FINISHED;
                        }
                }

                if (!notFinished) {
                        if (!getCurRepet ()) {
                                transition (FINISHED);
                        }
                        else {
                                if (!linked) {
                                        --currentRepetition;
                                }

                                transition (FORWARD);
                        }
                }
        }
        else if (state == FINISHED) {
                return;
        }
}

/****************************************************************************/

AtomicTween *AtomicTween::target (unsigned int property, double value, bool abs)
{
        if (!accessor) {
                accessor = Manager::getMain ()->getAccessor (property);
                targetValue = value;
                absolute = abs;
        }
        else {
                AtomicTween *tween = AtomicTween::create ();
                tween->equation = equation;
                tween->durationMs = durationMs;
                tween->object = object;
                tween->accessor = Manager::getMain ()->getAccessor (property);
                tween->targetValue = value;
                tween->absolute = abs;
                tween->linked = this;
                addTween (tween);
        }

        return this;
}

/****************************************************************************/

void AtomicTween::addTween (ITween *tween)
{
        if (!tweens.get ()) {
                tweens = std::auto_ptr <TweenVector> (new TweenVector);
        }

        tweens->push_back (tween);
}

} /* namespace Tween */
