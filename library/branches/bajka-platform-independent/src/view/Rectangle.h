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
#include "view/openGl/OpenGl.h"

namespace View {

/**
 * Rysuje prostokąt.
 * \ingroup View
 */
class Rectangle : public Primitive {
public:

        C__ (void)
        b_ ("Primitive")

        Rectangle ();
        virtual ~Rectangle ();
        virtual void update (Model::IModel *model, Event::UpdateEvent *e, Util::IShell *shell);

private:

        GLuint buffer;

        E_ (Rectangle)
};

} /* namespace View */

#	endif /* CIRCLE_H_ */
