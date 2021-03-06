/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef WITH_CHIPMUNK
#include "geometry/AffineMatrix.h"
#include "Space.h"
#include "util/Exceptions.h"
#include <chipmunk.h>

namespace Model {

cpSpace *Space::space = NULL;

/****************************************************************************/

cpSpace *Space::getSpace ()
{
        return space;
}

/****************************************************************************/

Space::Space ()
{
    	assertThrow (!space, "Space::Space : space is NULL");
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
        return Geometry::makePoint (g.x, g.y);
}

/****************************************************************************/

void Space::setGravity (Geometry::Point const &g)
{
        cpSpaceSetGravity (space, cpv (g.x, g.y));
}

/****************************************************************************/

IModel *Space::findContains (Geometry::Point const &point)
{
        Geometry::Point p = point;
        //? Czy to tu ma być?
        getMatrix ().transform (&p);
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

/****************************************************************************/

void Space::update (Event::UpdateEvent *e, Util::UpdateContext *uCtx)
{
        // Run chipmunk
        if (space) {
                cpSpaceStep (space, 1.0 / 60.0);
        }

        Group::update (e, shell);
}

} /* namespace Model */

#endif
