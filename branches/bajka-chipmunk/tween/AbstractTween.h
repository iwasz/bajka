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

        AbstractTween () : started (false), finished (false), yoyo (false), repetitions (0), delayMs (0) {}
        virtual ~AbstractTween () {}

        bool getFinished () const { return finished; }
        bool getStarted () const { return started; }
        void start (Manager *m = NULL);

        ITween *repeat (unsigned int num, bool yoyo = false);
        ITween *delay (unsigned int duration);

protected:

        bool started;
        bool finished;
        bool yoyo;
        unsigned int repetitions;
        unsigned int delayMs;

};

} /* namespace Tween */

#	endif /* ABSTRACTTWEEN_H_ */
