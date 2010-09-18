/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef OBSERVERWITHMAPPING_H_
#define OBSERVERWITHMAPPING_H_

#include <Pointer.h>
#include "AbstractObserver.h"

namespace Controller {
class IMapping;
}

namespace Event {

/**
 * Obserwator, ktory w każdej metodzie obsługi wywołuje metodę IMapping::run.
 * Należy ustawić mu zadany mapping, oraz w metodzie setBitMask ustawić na
 * jakie eventy ma reagować.
 * \ingroup Events
 */
class ObserverWithMapping : public AbstractObserver {
public:
        __c (void)
        _b ("AbstractObserver")

        virtual ~ObserverWithMapping () {}

        Ptr<Controller::IMapping> getMapping () const { return mapping; }

        /**
         * Ustawia mapping. Każda metoda
         */
        _m (setMapping) void setMapping (Ptr<Controller::IMapping> mapping) { this->mapping = mapping; }

        virtual bool onButtonPress (ButtonPressEvent *e);
        virtual bool onButtonRelease (ButtonReleaseEvent *e);
        virtual bool onMouseMotion (MouseMotionEvent *e);
        virtual bool onKeyDown (KeyDownEvent *e);
        virtual bool onKeyUp (KeyUpEvent *e);
        virtual bool onTimer (TimerEvent *e);
        virtual bool onQuit (QuitEvent *e);

private:

        Ptr <Controller::IMapping> mapping;

        _e (ObserverWithMapping)
};

}

#	endif /* OBSERVERWITHMAPPING_H_ */
