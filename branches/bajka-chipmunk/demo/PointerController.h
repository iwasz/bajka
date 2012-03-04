/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef POINTERCONTROLLER_H_
#define POINTERCONTROLLER_H_

#include "../controller/EmptyController.h"
#include "../geometry/Point.h"

namespace Demo {

class PointerController : public Controller::EmptyController {
public:
        C__ (void)
        b_ ("EmptyController")

        virtual ~PointerController () {}
        virtual bool onMouseMotion (Event::MouseMotionEvent *e, Model::IModel *m, View::IView *v);

        S_ (setPointer)
        void setPointer (Model::IModel *p) { pointer = p; }

        m_ (setOffset)
        void setOffset (Geometry::Point const &p) { offset = p; }

private:

        Model::IModel *pointer;
        Geometry::Point offset;

        E_ (PointerController)
};

} /* namespace Demo */

#	endif /* POINTERCONTROLLER_H_ */
