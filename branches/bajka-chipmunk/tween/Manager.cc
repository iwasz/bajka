/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Manager.h"
#include <iostream>
#include "../tween/ease/Ease.h"
#include "../tween/accessor/AffineAccessor.h"

namespace Tween {

Manager *Manager::main = NULL;

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
        equations[QUAD_IN      ] = new Linear;
        equations[QUAD_OUT     ] = new Linear;
        equations[QUAD_INOUT   ] = new Linear;
        equations[CUBIC_IN     ] = new CubicIn;
        equations[CUBIC_OUT    ] = new CubicOut;
        equations[CUBIC_INOUT  ] = new CubicInOut;
        equations[QUART_IN     ] = new Linear;
        equations[QUART_OUT    ] = new Linear;
        equations[QUART_INOUT  ] = new Linear;
        equations[QUINT_IN     ] = new Linear;
        equations[QUINT_OUT    ] = new Linear;
        equations[QUINT_INOUT  ] = new Linear;
        equations[CIRC_IN      ] = new Linear;
        equations[CIRC_OUT     ] = new Linear;
        equations[CIRC_INOUT   ] = new Linear;
        equations[SINE_IN      ] = new Linear;
        equations[SINE_OUT     ] = new Linear;
        equations[SINE_INOUT   ] = new Linear;
        equations[EXPO_IN      ] = new Linear;
        equations[EXPO_OUT     ] = new Linear;
        equations[EXPO_INOUT   ] = new Linear;
        equations[BACK_IN      ] = new BackIn;
        equations[BACK_OUT     ] = new BackOut;
        equations[BACK_INOUT   ] = new BackInOut;
        equations[BOUNCE_IN    ] = new BounceIn;
        equations[BOUNCE_OUT   ] = new BounceOut;
        equations[BOUNCE_INOUT ] = new BounceInOut;
        equations[ELASTIC_IN   ] = new Linear;
        equations[ELASTIC_OUT  ] = new Linear;
        equations[ELASTIC_INOUT] = new Linear;

        accessors[X] = new TranslateXAccessor;
        accessors[Y] = new TranslateYAccessor;
        accessors[SCALE] = new ScaleAccessor;
        accessors[ANGLE] = new AngleAccessor;
}

/****************************************************************************/

Manager::~Manager()
{
        // TODO skasowac equationsy
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
