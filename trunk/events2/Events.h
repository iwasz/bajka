/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EVENTS_H_
#define EVENTS_H_

/**
 * \defgroup Events
 * Podsystem eventów. W tym module znajdują się klasy implementujące poszczególne eventy, oraz serwisy
 * implementujące generowanie tych eventów.
 * \{
 * \}
 */

#include "IEvent.h"
#include "MouseButtonEvent.h"
#include "MouseMotionEvent.h"
#include "KeyboardEvent.h"
#include "TimerEvent.h"
#include "Common.h"
#include "QuitEvent.h"

#include "sdl/Sdl.h"

namespace Event {

}

#	endif /* EVENTS_H_ */
