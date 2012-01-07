/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef RECTANGLE_VIEW_H_
#define RECTANGLE_VIEW_H_

#include "AbstractWidget.h"

namespace Model {
class Box;
}

namespace View {

/**
 * Rysuje prostokąt.
 * \ingroup View
 */
class Rectangle : public AbstractWidget {
public:
        __c (void)
        _b ("AbstractWidget")

        Rectangle () : box () {}
        virtual ~Rectangle () {}

        virtual void setModel (Ptr <Model::IModel> model);
        virtual void doDraw ();

// Żeby nie trzeba było kastowac modelu na box w pochodnych.
protected:

        Model::Box *box;
        _e (Rectangle)
};

}

#	endif /* RECTANGLE_H_ */
