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

void AtomicTween::Target::init ()
{
	assertThrow (accessor, "AtomicTween::init : !accessor");

	if (tween->type == AtomicTween::TO) {
	        startValue = accessor->getValue (tween->object);
	}
	else {
                endValue = accessor->getValue (tween->object);
	}
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
        AtomicTween *tween = Manager::getMain ()->newAtomicTween ();
        tween->equation = Manager::getMain ()->getEase (ease);
        tween->durationMs = durationMs;
        tween->object = targetObject;
        tween->type = AtomicTween::TO;
        return tween;
}

/****************************************************************************/

AtomicTween *from (void *targetObject, unsigned int durationMs, Ease ease)
{
        AtomicTween *tween = Manager::getMain ()->newAtomicTween ();
        tween->equation = Manager::getMain ()->getEase (ease);
        tween->durationMs = durationMs;
        tween->object = targetObject;
        tween->type = AtomicTween::FROM;
        return tween;
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

AtomicTween *AtomicTween::abs (unsigned int property, double value)
{
        return target (Manager::getMain ()->getAccessor (property), value, true);
}

/****************************************************************************/

AtomicTween *AtomicTween::abs (std::string const &property, double value)
{
        return target (Manager::getMain ()->getAccessor (property), value, true);
}

/****************************************************************************/

AtomicTween *AtomicTween::rel (unsigned int property, double value)
{
        return target (Manager::getMain ()->getAccessor (property), value, false);
}

/****************************************************************************/

AtomicTween *AtomicTween::rel (std::string const &property, double value)
{
        return target (Manager::getMain ()->getAccessor (property), value, false);
}

/****************************************************************************/

AtomicTween *AtomicTween::target (IAccessor const *accessor, double value, bool abs)
{
        Target *target = Manager::getMain ()->newTarget ();
//        target->accessor = Manager::getMain ()->getAccessor (property);
        target->accessor = accessor;

        if (type == TO) {
                target->endValue = value;
        }
        else if (type == FROM) {
                target->startValue = value;
        }

        target->absolute = abs;
        target->tween = this;
        targets.push_back (target);
        return this;
}

} /* namespace Tween */
