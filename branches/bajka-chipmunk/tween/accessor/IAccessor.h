/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_IACCESSOR_H_
#define BAJKA_IACCESSOR_H_

namespace Tween {

struct IAccessor {
        virtual ~IAccessor () {}
        virtual double getValue (void *obj) const = 0;
        virtual void setValue (void *obj, double value) = 0;
};

} /* namespace Tween */

#	endif /* IACCESSOR_H_ */
