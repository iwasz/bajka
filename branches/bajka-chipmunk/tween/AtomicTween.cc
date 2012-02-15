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

void AtomicTween::initEntry (bool reverse) {}
void AtomicTween::initExit (bool reverse)
{
	currentRepetition = repetitions;
//        currentMs = ((forward) ? (0) : (durationMs));

	for (TargetVector::iterator i = targets.begin (); i != targets.end (); ++i) {
		(*i)->init ();
	}
}
void AtomicTween::delayEntry (bool reverse)
{
        currentMs = 0;
}
void AtomicTween::delayExit (bool reverse)
{
}
void AtomicTween::runEntry (bool reverse)
{
        currentMs = ((forward ^ reverse) ? (0) : (durationMs));
}
void AtomicTween::runExit (bool reverse) {}
void AtomicTween::finishedEntry  (bool reverse) {}
void AtomicTween::finishedExit (bool reverse)
{
	currentRepetition = repetitions;
}

/****************************************************************************/

void AtomicTween::updateRun (int deltaMs, bool direction)
{
        // Wylicz currentMs
        if (direction) {
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

        // Tweenuj
        for (TargetVector::iterator i = targets.begin(); i != targets.end(); ++i) {
                (*i)->update ();
        }
}

/****************************************************************************/

bool AtomicTween::checkEnd (bool direction)
{
        return (direction && currentMs >= durationMs) || (!direction && currentMs <= 0);
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
