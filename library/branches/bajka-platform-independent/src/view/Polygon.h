/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_POLY_H_
#define BAJKA_VIEW_POLY_H_

#include "Primitive.h"
#include "view/openGl/OpenGl.h"

namespace View {

/**
 * Rysuje prostokąt.
 * \ingroup View
 */
class Polygon : public Primitive {
public:

        C__ (void)
        b_ ("Primitive")

        Polygon ();
        virtual ~Polygon ();
        virtual void update (Model::IModel *model, Event::UpdateEvent *e, View::GLContext *ctx);

private:

        GLuint buffer;

        E_ (Polygon)
};

} /* namespace View */

#	endif /* CIRCLE_H_ */
