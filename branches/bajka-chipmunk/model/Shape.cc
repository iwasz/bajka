/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <chipmunk.h>
#include "../geometry/AffineMatrix.h"
#include "Shape.h"
#include "Body.h"
#include "../util/Exceptions.h"

namespace Model {

Shape::~Shape ()
{
        cpShapeFree (shape);
}

void Shape::parentCallback (IModel *m)
{
        AbstractModel::parentCallback (m);
        // TODO można zrobic cast w zalezności od define DEBUG/RELEASE.
        Body *body = static_cast <Body *> (m);
        double inertia = calculateInertia (body->getMass ());
        body->addInertia (inertia);
}

} /* namespace Model */
