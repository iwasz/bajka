/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Manager.h"
#include <iostream>

namespace Tween {

Manager *Manager::main = NULL;

void Manager::update (int deltaMs)
{
//	assertThrow (tween, "Manager::update : !tween");

	if (tween) {
		tween->update (deltaMs);
	}
}


} /* namespace Tween */
