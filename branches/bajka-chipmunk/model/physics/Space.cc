/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "../geometry/AffineMatrix.h"
#include "Space.h"
#include "../util/Exceptions.h"

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

IModel *Space::findContains (Geometry::Point const &point)
{
        Geometry::Point p = point;
        //? Czy to tu ma być?
        transform (&p);
        cpShape *shape = cpSpacePointQueryFirst (space, cpv (p.x, p.y), 0xFFFF, CP_NO_GROUP);

        if (shape) {
                cpDataPointer ptr = cpShapeGetUserData (shape);

                if (ptr) {
                        return static_cast<IModel *> (ptr);
                }
                else {
                        throw Util::RuntimeException ("cpDataPointer is NULL - fatal!");
                }
        }
        else {
                // Kastuj na kontener?
                IModel *ret;

                for (ModelVector::iterator i = begin (); i != end (); ++i) {
                        if ((ret = (*i)->findContains (p))) {
                                return ret;
                        }
                }
        }

        // Space się rozciąga na cały obszar, więc jesli nie ma dzieci, to zwróć space.
        return this;
}

} /* namespace Model */
