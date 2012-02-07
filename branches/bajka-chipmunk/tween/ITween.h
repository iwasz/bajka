/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_TWEEN_ITWEEN_H_
#define BAJKA_TWEEN_ITWEEN_H_

namespace Tween {

class ITween {
public:
        virtual ~ITween () {}
        virtual void update (int deltaMs) = 0;
};

} /* namespace Tween */

#	endif /* ITWEEN_H_ */
