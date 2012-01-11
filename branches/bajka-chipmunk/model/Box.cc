/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <chipmunk.h>
#include "Box.h"
#include "Body.h"
#include "Space.h"

namespace Model {

double Box::calculateInertia (double mass) const
{
        return cpMomentForBox (mass, width, height);
}

void Box::parentCallback (IModel *m)
{
        Body *b = static_cast <Body *> (m);
        shape = cpSpaceAddShape (Space::getSpace(), cpBoxShapeNew (b->getBody (), width, height));
        cpShapeSetElasticity (shape, 1.0f);
        cpShapeSetFriction (shape, 1.0f);
//#define GRABABLE_MASK_BIT (1<<31)
//#define NOT_GRABABLE_MASK (~GRABABLE_MASK_BIT)
//        cpShapeSetLayers(shape, NOT_GRABABLE_MASK);

        Shape::parentCallback (m);
}

} /* namespace Model1 */
