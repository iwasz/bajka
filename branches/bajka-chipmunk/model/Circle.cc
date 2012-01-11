/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Circle.h"
#include "../util/Exceptions.h"
#include "Body.h"
#include "Space.h"

namespace Model {

void Circle::setPosition (Geometry::Point const &p)
{
        if (getParent ()) {
                throw Util::OperationNotSupportedException ();
        }

        position = p;
}

Geometry::Point Circle::getPosition () const
{
        cpVect v = cpCircleShapeGetOffset (shape);
        return Geometry::Point (v.x, v.y);
}

double Circle::calculateInertia (double mass) const
{
        return cpMomentForCircle (mass, 0, getRadius (), cpv (getPosition ().getX (), getPosition ().getY ()));
}

void Circle::parentCallback (IModel *m)
{
        Body *b = static_cast <Body *> (m);
        shape = cpSpaceAddShape (Space::getSpace(), cpCircleShapeNew (b->getBody (), radius, cpv (position.getX (), position.getY ())));
        cpShapeSetElasticity (shape, 1.0f);
        cpShapeSetFriction (shape, 1.0f);
        Shape::parentCallback (m);
}

double Circle::getRadius () const
{
        return cpCircleShapeGetRadius (shape);
}

void Circle::setRadius (double r)
{
        if (getParent ()) {
                throw Util::OperationNotSupportedException ();
        }

        radius = r;
}


} /* namespace Model */
