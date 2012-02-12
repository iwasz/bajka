/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Manager.h"
#include <iostream>
#include "../tween/ease/Linear.h"
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
        equations[LINEAR_INOUT] = new Linear;

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
		tween->update (deltaMs);
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
