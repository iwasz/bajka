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

namespace Model {

double Box::calculateInertia (double mass) const
{
        return cpMomentForBox (mass, width, height);
}

void Box::parentCallback (IModel *m)
{
        Body *b = static_cast <Body *> (m);
        shape = cpBoxShapeNew (b->getBody (), width, height);
        Shape::parentCallback (m);
}

} /* namespace Model1 */
