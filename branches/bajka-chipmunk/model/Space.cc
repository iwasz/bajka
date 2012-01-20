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

/****************************************************************************/

Space::Space ()
{
        assert (!space);
        space = cpSpaceNew ();
}

/****************************************************************************/

Space::~Space ()
{
        cpSpaceFree (space);
}

/****************************************************************************/

Geometry::Point Space::getGravity () const
{
        cpVect g = cpSpaceGetGravity (space);
        return Geometry::Point (g.x, g.y);
}

/****************************************************************************/

void Space::setGravity (Geometry::Point const &g)
{
        cpSpaceSetGravity (space, cpv (g.getX (), g.getY ()));
}

/****************************************************************************/

IModel *Space::findChild (Geometry::Point const &p)
{
        cpShape *shape = cpSpacePointQueryFirst (space, cpv (p.x, p.y), 0xFFFF, CP_NO_GROUP);

        if (!shape) {
                return this;
        }

        cpDataPointer ptr = cpShapeGetUserData (shape);

        if (ptr) {
                return static_cast <IModel *> (ptr);
        }

        return NULL;
}

} /* namespace Model */
