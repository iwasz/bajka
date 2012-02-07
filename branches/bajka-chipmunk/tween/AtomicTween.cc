/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AtomicTween.h"

namespace Tween {

void AtomicTween::update (int deltaMs)
{
	if (finished) {
		return;
	}

	currentMs += deltaMs;
	double deltaValue = targetValue - startValue;
	double comuted = equation->compute (currentMs, startValue, deltaValue, durationMs);
	accessor->setValue (object, comuted);

	if (currentMs >= durationMs) {
		finished = true;
	}
}

} /* namespace Tween */
