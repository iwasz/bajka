/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TWEEN_FACTORY_H_
#define TWEEN_FACTORY_H_

#include "ITargetResolver.h"
#include <core/Object.h>

namespace Tween {
class ITween;

/**
 * Interfejs fabryki tweenów. Definicję podajemy (raczej) JSONem, a tatget objecty
 * są resolvowane w metodzie resolve i to ona definiuje jak podajemy referencję
 * do targetów.
 */
struct ITweenFactory : public ITargetResolver, public Core::Object {
        virtual ~ITweenFactory () {}
        virtual Tween::ITween *create () = 0;
};

} // nam

#endif /* TWEENPARSER_H_ */
