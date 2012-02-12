/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AtomicTween.h"
#include "Manager.h"
#include "Functions.h"

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

void AtomicTween::update (int deltaMs)
{
	if (finished) {
		return;
	}

	currentMs += deltaMs;
	double deltaValue = targetValue - startValue;
	double comuted = equation->compute (currentMs, startValue, deltaValue, durationMs);
	accessor->setValue (object, comuted);
	bool notFinished = currentMs < durationMs;

	if (tweens.get ()) {
	        for (TweenVector::iterator i = tweens->begin (); i != tweens->end (); ++i) {
	                (*i)->update (deltaMs);
	                notFinished |= !(*i)->getFinished ();
	        }
	}

	finished = !notFinished;
}

/****************************************************************************/

AtomicTween *AtomicTween::target (unsigned int property, double value, bool abs)
{
        if (!accessor) {
                accessor = Manager::getMain ()->getAccessor (property);
                startValue = accessor->getValue (object);
                targetValue = (abs) ? (startValue + value) : (value);
        }
        else {
                AtomicTween *tween = AtomicTween::create ();
                tween->equation = equation;
                tween->durationMs = durationMs;
                tween->object = object;
                tween->accessor = Manager::getMain ()->getAccessor (property);
                tween->startValue = tween->accessor->getValue (object);
                tween->targetValue = (abs) ? (tween->startValue + value) : (value);
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
