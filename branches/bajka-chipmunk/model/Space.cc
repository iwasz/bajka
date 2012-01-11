/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "../geometry/AffineMatrix.h"
#include "Space.h"

namespace Model {

cpSpace *Space::space = NULL;

Space::Space ()
{
        assert (!space);
        space = cpSpaceNew ();
}

Space::~Space ()
{
        cpSpaceFree (space);
}

Geometry::Point Space::getGravity () const
{
        cpVect g = cpSpaceGetGravity (space);
        return Geometry::Point (g.x, g.y);
}

void Space::setGravity (Geometry::Point const &g)
{
        cpSpaceSetGravity (space, cpv (g.getX (), g.getY ()));
}

} /* namespace Model */