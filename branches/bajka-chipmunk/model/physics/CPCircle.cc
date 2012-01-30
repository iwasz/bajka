/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "CPCircle.h"
#include "../util/Exceptions.h"
#include "Body.h"
#include "Space.h"

namespace Model {

void CPCircle::setOrigin (Geometry::Point const &p)
{
        if (getParent ()) {
                throw Util::OperationNotSupportedException ();
        }

        origin = p;
}

/****************************************************************************/

Geometry::Point CPCircle::getOrigin () const
{
        cpVect v = cpCircleShapeGetOffset (shape);
        return Geometry::Point (v.x, v.y);
}

/****************************************************************************/

void CPCircle::parentCallback (IModel *m)
{
        Body *b = static_cast <Body *> (m);
        shape = cpSpaceAddShape (Space::getSpace(), cpCircleShapeNew (b->getBody (), radius, cpv (origin.x, origin.y)));
        cpShapeSetUserData (shape, this);

        // TODO można zrobic cast w zalezności od define DEBUG/RELEASE.
        b->addInertia (cpMomentForCircle (b->getMass (), 0, radius, cpv (origin.x, origin.y)));
        AbstractModel::parentCallback (m);
}

/****************************************************************************/

double CPCircle::getRadius () const
{
        return cpCircleShapeGetRadius (shape);
}

/****************************************************************************/

void CPCircle::setRadius (double r)
{
        if (getParent ()) {
                throw Util::OperationNotSupportedException ();
        }

        radius = r;
}


} /* namespace Model */
