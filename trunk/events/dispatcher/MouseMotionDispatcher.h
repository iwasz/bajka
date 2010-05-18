/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 19, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MOUSEMOTIONDISPATCHER_H_
#define MOUSEMOTIONDISPATCHER_H_

#include "IEvent.h"
#include "MouseMotionEvent.h"
#include "geometry/Box.h"

namespace Events {

// TODO zmieinć nazwę na Filter
class MouseMotionDispatcher : public AbstractObservable <MouseMotionEvent>, public IObserver <MouseMotionEvent> {
public:

        enum Mode { ALL, IN, OUT };

        MouseMotionDispatcher () : mode (ALL) {}
        virtual ~MouseMotionDispatcher () {}

        virtual void update (const IObservable <MouseMotionEvent> &observable, const MouseMotionEvent &event);

        const Geometry::Box &getArea () const { return area; }
        void setArea (const Geometry::Box  &area) { this->area = area; }

        Mode getMode () const { return mode; }
        void setMode (Mode mode) { this->mode = mode; }

private:

        Mode mode;
        Geometry::Box area;

};

}

#	endif /* MOUSEMOTIONDISPATCHER_H_ */
