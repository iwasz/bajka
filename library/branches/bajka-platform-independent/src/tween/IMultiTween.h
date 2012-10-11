/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMULTITWEEN_H_
#define IMULTITWEEN_H_

namespace Tween {
class TweeningProperty;

class IMultiTween {
public:
        virtual ~IMultiTween () {}

        virtual IMultiTween *add (ITween *tween) = 0;
        virtual void remove (ITween *tween) = 0;
};

} /* namespace Tween */
#endif /* IMULTITWEEN_H_ */
