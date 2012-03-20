/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_RESIZEEVENT_H_
#define BAJKA_RESIZEEVENT_H_

#include "IEvent.h"

namespace Event {

class ResizeEvent : public IEvent {
public:

        ResizeEvent () : width (0), height (0) {}
        virtual ~ResizeEvent () {}

        Type getType () const { return RESIZE_EVENT; }
        bool runCallback (Model::IModel *m, View::IView *v, Controller::IController *c, void *d) { return c->onResize (static_cast <ResizeEvent *> (this), m, v); }
        std::string toString () const;

        int getHeight () const { return height; }
        void setHeight (int height) { this->height = height; }

        int getWidth () const { return width; }
        void setWidth (int width) { this->width = width; }

private:

        int width;
        int height;

};

} /* namespace Event */

#	endif /* RESIZEEVENT_H_ */
