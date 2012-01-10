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

Geometry::Vector Space::getGravity () const
{
        cpVect g = cpSpaceGetGravity (space);
        return Geometry::Vector (g.x, g.y);
}

void Space::setGravity (Geometry::Vector const &g)
{
        cpSpaceSetGravity (space, cpv (g.getX (), g.getY ()));
}

double const *Space::getMatrix () const
{
        static Geometry::AffineMatrix one;
        return one.data ().begin ();
}

} /* namespace Model */
