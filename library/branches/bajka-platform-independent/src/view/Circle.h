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

namespace View {

/**
 * Rysuje okrąg.
 * \ingroup View
 */
class Circle : public Primitive {
public:

        // TODO zakomentowałem bop BOOST__PP_DEC działało tylko do 256
//        C__ (void)
//        b_ ("Primitive")

        virtual ~Circle () {}
        virtual void update (Model::IModel *model, Event::UpdateEvent *e, Util::IShell *shell);

//        E_ (View::Circle)
};

} /* namespace View */

#	endif /* CIRCLE_H_ */
