/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ABSTRACTTWEEN_H_
#define ABSTRACTTWEEN_H_

#include "ITween.h"
#include <cstddef>

namespace Tween {
class Manager;

class AbstractTween : public ITween {
public:

        AbstractTween () : finished (false) {}
        virtual ~AbstractTween () {}

        bool getFinished () const { return finished; }
        void start (Manager *m = NULL);

protected:

        bool finished;

};

} /* namespace Tween */

#	endif /* ABSTRACTTWEEN_H_ */
