/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_CIRCLE_H_
#define BAJKA_VIEW_CIRCLE_H_

#include "ReflectionMacros.h"
#include "Primitive.h"

namespace View {

/**
 * Rysuje prostokąt.
 * \ingroup View
 */
class Circle : public Primitive {
public:

        C__ (void)
        b_ ("Primitive")

        virtual ~Circle () {}
        virtual void update (Model::IModel *model);

        E_ (View::Circle)
};

} /* namespace View */

#	endif /* CIRCLE_H_ */
