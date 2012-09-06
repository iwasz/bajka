/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_CHIPMUNK
#ifndef BAJKA_MODEL_SHAPE_H_
#define BAJKA_MODEL_SHAPE_H_

#include "../../util/ReflectionMacros.h"
#include "../IModel.h"

struct cpShape;

namespace Model {

class Shape : public virtual Core::Object {
public:

        d__

        Shape () : shape (0) {}
        virtual ~Shape ();

        // Settery + gettery od shape.

protected:

        cpShape *shape;

        E_ (Shape)
};

} /* namespace Model */

#endif /* SHAPE_H_ */
#endif
