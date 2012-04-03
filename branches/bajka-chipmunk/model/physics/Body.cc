/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_CHIPMUNK
#include <chipmunk.h>
#include "../geometry/AffineMatrix.h"
#include "Body.h"
#include "Space.h"
#include "../../util/Exceptions.h"

namespace Model {

Body::Body ()
{
        assertThrow (Space::getSpace (), "Space::space == NULL");
        body = cpSpaceAddBody (Space::getSpace (), cpBodyNew (1, 1));
        cpBodySetUserData (body, this);
}

/****************************************************************************/

Body::~Body ()
{
        cpBodyFree (body);
        body = NULL;
}

/****************************************************************************/

Geometry::Point Body::getTranslate () const
{
        cpVect v = cpBodyGetPos (body);
        return Geometry::Point (v.x, v.y);
}

/****************************************************************************/

void Body::setTranslate (Geometry::Point const &p)
{
        cpBodySetPos (body, cpv (p.x, p.y));
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

#endif
