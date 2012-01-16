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
        shape = cpSpaceAddShape (Space::getSpace(), cpBoxShapeNew2 (b->getBody (),
                   cpBBNew (position.x, position.y, position.x + width, position.y + height)));
//        cpShapeSetElasticity (shape, 1.0f);
//        cpShapeSetFriction (shape, 1.0f);
        Shape::parentCallback (m);
}

} /* namespace Model1 */
