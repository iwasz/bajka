/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef TWEENINGPROPERTY_H_
#define TWEENINGPROPERTY_H_

#include <cstddef>
#include <list>

namespace Tween {
class IAccessor;

/**
 *
 */
struct TweeningProperty {

        TweeningProperty () : accessor (NULL), startValue (0), endValue (0), absolute (true) {}

        IAccessor const *accessor;
        double startValue;
        double endValue;
        bool absolute;
};

typedef std::list <TweeningProperty *> TweeningPropertyList;

} /* namespace Tween */
#endif /* TWEENINGPROPERTY_H_ */
