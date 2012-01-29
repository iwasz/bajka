/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <chipmunk.h>
#include "../geometry/AffineMatrix.h"
#include "Body.h"
#include "Space.h"

namespace Model {

Body::Body ()
{
        body = cpSpaceAddBody (Space::getSpace (), cpBodyNew (1, 1));
        cpBodySetUserData (body, this);
}

/****************************************************************************/

Body::~Body ()
{
//        TODO Coś jest źle przy kasowaniu kontenera - SegF tutaj.
//        cpBodyFree (body);
        body = NULL;
}

/****************************************************************************/

Geometry::Point Body::getPosition () const
{
        cpVect v = cpBodyGetPos (body);
        return Geometry::Point (v.x, v.y);
}

/****************************************************************************/

void Body::setPosition (Geometry::Point const &p)
{
        cpBodySetPos (body, cpv (p.getX (), p.getY ()));
        cpSpaceReindexShapesForBody (Space::getSpace (), body);
}

/****************************************************************************/

double Body::getAngle () const
{
        return cpBodyGetAngle (body);
}

/****************************************************************************/

void Body::setAngle (double a)
{
        cpBodySetAngle (body, a);
        cpSpaceReindexShapesForBody (Space::getSpace (), body);
}

/****************************************************************************/

double Body::getMass () const
{
        return cpBodyGetMass (body);
}

/****************************************************************************/

void Body::setMass (double m)
{
        cpBodySetMass (body, m);
}

/****************************************************************************/

double Body::getInertia () const
{
        return cpBodyGetMoment (body);
}

/****************************************************************************/

void Body::setInertia (double i)
{
        cpBodySetMoment (body, i);
}

/****************************************************************************/

void Body::addInertia (double i)
{
        double tmp = cpBodyGetMoment (body);
        cpBodySetMoment (body, i + tmp);
}

} /* namespace Model */
