/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_CIRCLE_H_
#define BAJKA_VIEW_CIRCLE_H_

#include "util/ReflectionMacros.h"
#include "Primitive.h"
#include "view/openGl/OpenGl.h"

namespace View {

/**
 * Rysuje okrąg.
 * \ingroup View
 */
class Circle : public Primitive {
public:

        C__ (void)
        b_ ("Primitive")

        Circle ();
        virtual ~Circle ();

        virtual void update (Model::IModel *model, Event::UpdateEvent *e, Util::IShell *shell);

private:

        GLuint buffer;

        E_ (View::Circle)
};

} /* namespace View */

#	endif /* CIRCLE_H_ */
