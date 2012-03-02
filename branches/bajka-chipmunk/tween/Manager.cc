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
#include "../tween/ease/Ease.h"
#include "../tween/accessor/AffineAccessor.h"
#include "../view/LoopImage.h"

namespace Tween {

Manager *Manager::main = NULL;

struct Pool {

        boost::object_pool <AtomicTween> atomicTweens;
        boost::object_pool <AtomicTween::Target> targets;
        boost::object_pool <Timeline> timelines;

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

AtomicTween::Target *Manager::newTarget ()
{
        AtomicTween::Target *ret = new (pool->targets.malloc ()) AtomicTween::Target;
        assertThrow (ret, "Manager::newTarget: failed to create object.")
        return ret;
}

/****************************************************************************/

void Manager::freeTarget (AtomicTween::Target *t)
{
//        t->clear ();
        pool->targets.free (t);
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
//        t->clear ();
        pool->timelines.free (t);
}

/**
 * Tworzy główny manager (singleton).
 */
void init ()
{
        Manager::init ();
}

/****************************************************************************/

void free ()
{
        Manager::free ();
}

/****************************************************************************/

Manager::Manager () : tween (NULL)
{
        equations[LINEAR_INOUT ] = new Linear;
        equations[QUAD_IN      ] = new QuadIn;
        equations[QUAD_OUT     ] = new QuadOut;
        equations[QUAD_INOUT   ] = new QuadInOut;
        equations[CUBIC_IN     ] = new CubicIn;
        equations[CUBIC_OUT    ] = new CubicOut;
        equations[CUBIC_INOUT  ] = new CubicInOut;
        equations[QUART_IN     ] = new QuartIn;
        equations[QUART_OUT    ] = new QuartOut;
        equations[QUART_INOUT  ] = new QuartInOut;
        equations[QUINT_IN     ] = new QuintIn;
        equations[QUINT_OUT    ] = new QuintOut;
        equations[QUINT_INOUT  ] = new QuintInOut;
        equations[CIRC_IN      ] = new CircIn;
        equations[CIRC_OUT     ] = new CircOut;
        equations[CIRC_INOUT   ] = new CircInOut;
        equations[SINE_IN      ] = new SineIn;
        equations[SINE_OUT     ] = new SineOut;
        equations[SINE_INOUT   ] = new SineInOut;
        equations[EXPO_IN      ] = new ExpoIn;
        equations[EXPO_OUT     ] = new ExpoOut;
        equations[EXPO_INOUT   ] = new ExpoInOut;
        equations[BACK_IN      ] = new BackIn;
        equations[BACK_OUT     ] = new BackOut;
        equations[BACK_INOUT   ] = new BackInOut;
        equations[BOUNCE_IN    ] = new BounceIn;
        equations[BOUNCE_OUT   ] = new BounceOut;
        equations[BOUNCE_INOUT ] = new BounceInOut;
        equations[ELASTIC_IN   ] = new ElasticIn;
        equations[ELASTIC_OUT  ] = new ElasticOut;
        equations[ELASTIC_INOUT] = new ElasticInOut;

        accessors[X] = new TranslateXAccessor;
        accessors[Y] = new TranslateYAccessor;
        accessors[SCALE] = new ScaleAccessor;
        accessors[ANGLE] = new AngleAccessor;
        accessors[LOOP_X] = new LoopImageXAccessor;
        accessors[LOOP_Y] = new LoopImageYAccessor;

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

void Manager::free ()
{
        delete main;
}

/****************************************************************************/

void Manager::update (int deltaMs)
{
//	assertThrow (tween, "Manager::update : !tween");

	if (tween) {
		tween->update (deltaMs, false);
	}
}

/****************************************************************************/

IEquation const *Manager::getEase (Ease e) const
{
        EquationMap::const_iterator i = equations.find (e);
        return (i != equations.end ()) ? (i->second) : NULL;
}

/****************************************************************************/

void Manager::registerAccessor (unsigned int id, IAccessor *a)
{
        accessors[id] = a;
}

/****************************************************************************/

IAccessor const *Manager::getAccessor (unsigned int id) const
{
        AccessorMap::const_iterator i = accessors.find (id);
        return (i != accessors.end ()) ? (i->second) : NULL;
}


} /* namespace Tween */
