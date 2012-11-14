/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_RECT_H_
#define BAJKA_VIEW_RECT_H_

#include "Primitive.h"

namespace View {

/**
 * Rysuje prostokąt.
 * \ingroup View
 */
class Rectangle : public Primitive {
public:

        C__ (void)
        b_ ("Primitive")

        virtual ~Rectangle () {}
        virtual void update (Model::IModel *model, Event::UpdateEvent *e, Util::IShell *shell);

        E_ (Rectangle)
};

} /* namespace View */

#	endif /* CIRCLE_H_ */
