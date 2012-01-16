/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_VIEW_POLYGON_H_
#define BAJKA_VIEW_POLYGON_H_

#include "ReflectionMacros.h"
#include "Primitive.h"

namespace View {

class Polygon : public Primitive {
public:

        C__ (void)
        b_ ("Primitive")

        virtual ~Polygon () {}
        virtual void update (Model::IModel *model) {}

        E_ (Polygon)
};

} // namespace

#	endif /* POLYGON_H_ */
