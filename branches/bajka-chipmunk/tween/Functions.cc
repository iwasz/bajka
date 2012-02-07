/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Functions.h"
#include "Manager.h"

namespace Tween {

/**
 * Tworzy główny manager (singleton).
 */
void init ()
{
	Manager::init ();
}

void free ()
{
	Manager::free ();
}

} /* namespace Tween */
