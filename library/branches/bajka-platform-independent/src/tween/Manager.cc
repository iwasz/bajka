/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <boost/pool/object_pool.hpp>
#include "Manager.h"
#include "Timeline.h"
#include "tween/ease/Ease.h"
#include "tween/accessor/AffineAccessor.h"
#include "view/LoopImage.h"
#include "MultiTween.h"
#include "SetTween.h"
#include "TweeningProperty.h"

namespace Tween {

Manager *Manager::main = NULL;

struct Pool {

        boost::object_pool <AtomicTween> atomicTweens;
        boost::object_pool <TweeningProperty> properties;
        boost::object_pool <Timeline> timelines;
        boost::object_pool <MultiTween> multiTweens;
        boost::object_pool <SetTween> setTweens;

};

/****************************************************************************/

AtomicTween *Manager::newAtomicTween ()
{
        /*
         * Placement new nie alokuje pamięci, a jedynie wywołuje konstruktor,
         * inicjując od nowa obiekt. Destruktora nie uruchamiamy, gdyz nie robi
         * on nic.
         */
        AtomicTween *ret = new (pool->atomicTweens.malloc ()) AtomicTween;
        assertThrow (ret, "Manager::newAtomicTween : failed to create AtomicTween.")
        return ret;
}

/****************************************************************************/

void Manager::freeAtomicTween (AtomicTween *a)
{
//        for (AtomicTween::TargetVector::iterator i = a->targets.begin (); i != a->targets.end (); ++i) {
//                freeTarget (*i);
//        }

//        Clear jest niepotrzebne, bo zawsze konstruktor się odpala.
//        a->clear ();
        pool->atomicTweens.free (a);
}

/****************************************************************************/

TweeningProperty *Manager::newProperty ()
{
        TweeningProperty *ret = new (pool->properties.malloc ()) TweeningProperty;
        assertThrow (ret, "Manager::newTarget: failed to create object.")
        return ret;
}

/****************************************************************************/

void Manager::freeProperty (TweeningProperty *t)
{
        pool->properties.free (t);
}

/****************************************************************************/

Timeline *Manager::newTimeline ()
{
        Timeline *ret = new (pool->timelines.malloc ()) Timeline;
        assertThrow (ret, "Manager::newTimeline : failed to create object.")
        return ret;
}

/****************************************************************************/

void Manager::freeTimeline (Timeline *t)
{
        pool->timelines.free (t);
}

/****************************************************************************/

MultiTween *Manager::newMultiTween ()
{
        MultiTween *ret = new (pool->multiTweens.malloc ()) MultiTween;
        assertThrow (ret, "Manager::newMultiTween : failed to create object.")
        return ret;
}

/****************************************************************************/

void Manager::freeMultiTween (MultiTween *t)
{
        pool->multiTweens.free (t);
}

/****************************************************************************/

SetTween *Manager::newSetTween ()
{
//        SetTween *ret = new (pool->setTweens.malloc ()) SetTween;
//        assertThrow (ret, "Manager::newSetTween : failed to create object.")
//        return ret;
        return NULL;
}

/****************************************************************************/

void Manager::freeSetTween (SetTween *t)
{
        pool->setTweens.free (t);
}

/****************************************************************************/

void Manager::free (ITween *t)
{
        if (typeid (*t) == typeid (AtomicTween)) {
                freeAtomicTween (dynamic_cast <AtomicTween *> (t));
        }
        else if (typeid (*t) == typeid (Timeline)) {
                freeTimeline (dynamic_cast <Timeline *> (t));
        }
        else if (typeid (*t) == typeid (MultiTween)) {
                freeMultiTween (dynamic_cast <MultiTween *> (t));
        }
        else if (typeid (*t) == typeid (SetTween)) {
                freeSetTween (dynamic_cast <SetTween *> (t));
        }
}

/**
 * Tworzy główny manager (singleton).
 */
void init ()
{
        Manager::init ();
}

/****************************************************************************/

void destroy ()
{
        Manager::destroy ();
}

/****************************************************************************/

#define registerEquationPrv(name,newStatement)  \
        {                                       \
                IEquation *e = newStatement;    \
                equations[name] = e;            \
                equationsStr[#name] = e;        \
        }

/****************************************************************************/

#define registerAccessorPrv(name,newStatement)  \
        {                                       \
                IAccessor *a = newStatement;    \
                accessors[name] = a;            \
                accessorsStr[#name] = a;        \
        }

/****************************************************************************/

Manager::Manager ()
{
        registerEquationPrv (LINEAR_INOUT , new Linear);
        registerEquationPrv (QUAD_IN      , new QuadIn);
        registerEquationPrv (QUAD_OUT     , new QuadOut);
        registerEquationPrv (QUAD_INOUT   , new QuadInOut);
        registerEquationPrv (CUBIC_IN     , new CubicIn);
        registerEquationPrv (CUBIC_OUT    , new CubicOut);
        registerEquationPrv (CUBIC_INOUT  , new CubicInOut);
        registerEquationPrv (QUART_IN     , new QuartIn);
        registerEquationPrv (QUART_OUT    , new QuartOut);
        registerEquationPrv (QUART_INOUT  , new QuartInOut);
        registerEquationPrv (QUINT_IN     , new QuintIn);
        registerEquationPrv (QUINT_OUT    , new QuintOut);
        registerEquationPrv (QUINT_INOUT  , new QuintInOut);
        registerEquationPrv (CIRC_IN      , new CircIn);
        registerEquationPrv (CIRC_OUT     , new CircOut);
        registerEquationPrv (CIRC_INOUT   , new CircInOut);
        registerEquationPrv (SINE_IN      , new SineIn);
        registerEquationPrv (SINE_OUT     , new SineOut);
        registerEquationPrv (SINE_INOUT   , new SineInOut);
        registerEquationPrv (EXPO_IN      , new ExpoIn);
        registerEquationPrv (EXPO_OUT     , new ExpoOut);
        registerEquationPrv (EXPO_INOUT   , new ExpoInOut);
        registerEquationPrv (BACK_IN      , new BackIn);
        registerEquationPrv (BACK_OUT     , new BackOut);
        registerEquationPrv (BACK_INOUT   , new BackInOut);
        registerEquationPrv (BOUNCE_IN    , new BounceIn);
        registerEquationPrv (BOUNCE_OUT   , new BounceOut);
        registerEquationPrv (BOUNCE_INOUT , new BounceInOut);
        registerEquationPrv (ELASTIC_IN   , new ElasticIn);
        registerEquationPrv (ELASTIC_OUT  , new ElasticOut);
        registerEquationPrv (ELASTIC_INOUT, new ElasticInOut);

        registerAccessorPrv (X, new TranslateXAccessor);
        registerAccessorPrv (Y, new TranslateYAccessor);
        registerAccessorPrv (SCALE, new ScaleAccessor);
        registerAccessorPrv (ANGLE, new AngleAccessor);

        pool = std::auto_ptr <Pool> (new Pool);
}

/****************************************************************************/

Manager::~Manager()
{
        // TODO skasowac equationsy i accessory.
}

/****************************************************************************/

void Manager::init ()
{
        main = new Manager;
}

/****************************************************************************/

void Manager::destroy ()
{
        delete main;
}

/****************************************************************************/

void Manager::update (int deltaMs)
{
        for (TweenList::iterator i = tweens.begin (); i != tweens.end (); ++i) {
                (*i)->update (deltaMs, false);
        }
}

/****************************************************************************/

IEquation const *Manager::getEase (Ease e) const
{
        EquationMap::const_iterator i = equations.find (e);
        return (i != equations.end ()) ? (i->second) : NULL;
}

/****************************************************************************/

IEquation const *Manager::getEase (std::string const &s) const
{
        EquationMapStr::const_iterator i = equationsStr.find (s);
        return (i != equationsStr.end ()) ? (i->second) : NULL;
}

/****************************************************************************/

void Manager::registerAccessor (unsigned int id, std::string const &s, IAccessor *a)
{
        accessors[id] = a;
        accessorsStr[s] = a;
}

/****************************************************************************/

IAccessor const *Manager::getAccessor (unsigned int id) const
{
        AccessorMap::const_iterator i = accessors.find (id);
        return (i != accessors.end ()) ? (i->second) : NULL;
}

/****************************************************************************/

IAccessor const *Manager::getAccessor (std::string const &s) const
{
        AccessorMapStr::const_iterator i = accessorsStr.find (s);
        return (i != accessorsStr.end ()) ? (i->second) : NULL;
}

/****************************************************************************/

IMultiTween *Manager::add (ITween *tween)
{
        tween->setParent (this);
        tweens.push_back (tween);
        return this;
}

/****************************************************************************/

void Manager::remove (ITween *tween)
{
        tweens.remove (tween);
        free (tween);
}

/****************************************************************************/

void Manager::remove (void const *target, bool onlyActive)
{
        for (TweenList::iterator i = tweens.begin (); i != tweens.end (); ++i) {
                (*i)->remove (target, onlyActive);
        }
}

/****************************************************************************/

void Manager::remove (void const *target, TweeningProperty *property, bool onlyActive)
{
        for (TweenList::iterator i = tweens.begin (); i != tweens.end (); ++i) {
                (*i)->remove (target, property, onlyActive);
        }
}

/****************************************************************************/

void Manager::overwrite (ITargetable const *tween)
{
        switch (tween->getOverwrite ()) {
        case ITargetable::ALL_IMMEDIATE:
        case ITargetable::ALL_ONSTART:
                remove (tween->getTarget (), false);
                break;

        case ITargetable::AUTO:
//                remove (tween->getTarget (), );
                break;

        case ITargetable::CONCURRENT:
                remove (tween->getTarget (), true);
                break;

        case ITargetable::NONE:
        default:
                break;
        }

}

} /* namespace Tween */
