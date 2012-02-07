/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_TWEEN_ITWEEN_H_
#define BAJKA_TWEEN_ITWEEN_H_

#include <vector>
#include <list>

namespace Tween {

class ITween {
public:
        virtual ~ITween () {}
        virtual void update (int deltaMs) = 0;
        virtual bool getFinished () const = 0;
};

typedef std::vector <ITween *> TweenVector;
typedef std::list <ITween *> TweenList;

} /* namespace Tween */

#	endif /* ITWEEN_H_ */
