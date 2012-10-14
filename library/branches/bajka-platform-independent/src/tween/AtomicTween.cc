/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AtomicTween.h"
#include "Manager.h"
#include "IMultiTween.h"

namespace Tween {

AtomicTween *to (void *targetObject, unsigned int durationMs, Ease ease, ITargetable::Overwrite o)
{
        AtomicTween *tween = Manager::getMain ()->newAtomicTween ();
        tween->equation = Manager::getMain ()->getEase (ease);
        tween->durationMs = durationMs;
        tween->object = targetObject;
        tween->type = AtomicTween::TO;
        tween->setOverwrite (o);

        if (o == ITargetable::ALL_IMMEDIATE) {
                Manager::getMain ()->overwrite (tween);
        }

        return tween;
}

/****************************************************************************/

AtomicTween *from (void *targetObject, unsigned int durationMs, Ease ease, ITargetable::Overwrite o)
{
        AtomicTween *tween = Manager::getMain ()->newAtomicTween ();
        tween->equation = Manager::getMain ()->getEase (ease);
        tween->durationMs = durationMs;
        tween->object = targetObject;
        tween->type = AtomicTween::FROM;
        tween->setOverwrite (o);

        if (o == ITargetable::ALL_IMMEDIATE) {
                Manager::getMain ()->overwrite (tween);
        }

        return tween;
}

/****************************************************************************/

AtomicTween::AtomicTween () :
        AbstractTween (),
        equation (NULL),
        durationMs (0),
        object (NULL),
        type (TO),
        overwrite (ALL_IMMEDIATE),
        parent (NULL)
{
}

/****************************************************************************/

void AtomicTween::initEntry (bool reverse) {}
void AtomicTween::initExit (bool reverse)
{
	currentRepetition = repetitions;
//        currentMs = ((forward) ? (0) : (durationMs));

	for (TweeningPropertyList::iterator i = properties.begin (); i != properties.end (); ++i) {
	        TweeningProperty *tp = *i;

                assertThrow (tp->accessor, "AtomicTween::init : !accessor");

                if (type == AtomicTween::TO) {
                        tp->startValue = tp->accessor->getValue (object);
                }
                else {
                        tp->endValue = tp->accessor->getValue (object);
                }
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
        if (overwrite == ITargetable::ALL_ONSTART) {
                Manager::getMain ()->overwrite (this);
        }

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
        for (TweeningPropertyList::iterator i = properties.begin (); i != properties.end (); ++i) {
                TweeningProperty *tp = *i;

                double deltaValue = tp->endValue - ((tp->absolute) ? (tp->startValue) : (0));
                double computed = equation->compute (currentMs, tp->startValue, deltaValue, durationMs);
                tp->accessor->setValue (object, computed);
        }
}

/****************************************************************************/

bool AtomicTween::checkEnd (bool direction)
{
        return (direction && currentMs >= durationMs) || (!direction && currentMs <= 0);
}

/****************************************************************************/

AtomicTween *AtomicTween::abs (unsigned int prop, double value)
{
        return property (Manager::getMain ()->getAccessor (prop), value, true);
}

/****************************************************************************/

AtomicTween *AtomicTween::abs (std::string const &prop, double value)
{
        return property (Manager::getMain ()->getAccessor (prop), value, true);
}

/****************************************************************************/

AtomicTween *AtomicTween::rel (unsigned int prop, double value)
{
        return property (Manager::getMain ()->getAccessor (prop), value, false);
}

/****************************************************************************/

AtomicTween *AtomicTween::rel (std::string const &prop, double value)
{
        return property (Manager::getMain ()->getAccessor (prop), value, false);
}

/****************************************************************************/

AtomicTween *AtomicTween::property (IAccessor const *accessor, double value, bool abs)
{
        TweeningProperty *property = Manager::getMain ()->newProperty ();
        property->accessor = accessor;

        if (type == TO) {
                property->endValue = value;
        }
        else if (type == FROM) {
                property->startValue = value;
        }

        property->absolute = abs;
        properties.push_back (property);
        return this;
}

/****************************************************************************/

void AtomicTween::removeProperty (IAccessor *a)
{
        throw 1;
}

/****************************************************************************/

void AtomicTween::remove (void const *target, bool onlyActive)
{
        if (target && target != this->object) {
                return;
        }

        if (onlyActive && (getState () != DELAY && getState () != RUN)) {
                return;
        }

        parent->remove (this);
}

/****************************************************************************/

void AtomicTween::remove (void const *target, TweeningProperty *property, bool onlyActive)
{
        if (target != this->object) {
                return;
        }

}


} /* namespace Tween */
