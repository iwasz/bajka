/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SETTWEEN_H_
#define BAJKA_SETTWEEN_H_

#include "AbstractTween.h"

namespace Tween {

/**
 * Tween ustawiający zadaną wartość natychmiast, bez interpolacji.
 * \ingroup Tween
 */
class SetTween : public AbstractTween {
public:
        virtual ~SetTween () {}
};

} /* namespace Tween */

#	endif /* SETTWEEN_H_ */
