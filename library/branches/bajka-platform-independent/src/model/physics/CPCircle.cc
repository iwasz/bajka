/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_CHIPMUNK
#include <chipmunk.h>
#include "CPCircle.h"
#include "util/Exceptions.h"
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
        return Geometry::makePoint (v.x, v.y);
}

/****************************************************************************/

void CPCircle::onParentSet (IModel *m)
{
        Body *b = dynamic_cast <Body *> (m);
        assertThrow (b, "CPCircle::onParentSet : dynamic_cast <Body *> (m) failed");

        shape = cpSpaceAddShape (Space::getSpace(), cpCircleShapeNew (b->getBody (), radius, cpv (origin.x, origin.y)));
        cpShapeSetUserData (shape, this);

        // TODO można zrobic cast w zalezności od define DEBUG/RELEASE.
        b->addInertia (cpMomentForCircle (b->getMass (), 0, radius, cpv (origin.x, origin.y)));
        AbstractModel::onParentSet (m);
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

/****************************************************************************/

Geometry::Box CPCircle::getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const
{
	cpBB b = cpShapeGetBB (shape);
	return Geometry::Box (b.l, b.b, b.r, b.t);
}

} /* namespace Model */

#endif
