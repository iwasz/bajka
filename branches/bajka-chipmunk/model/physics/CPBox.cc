/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <chipmunk.h>
#include "CPBox.h"
#include "Body.h"
#include "Space.h"

namespace Model {

Geometry::Point CPBox::getPosition () const
{
        return box.ll;
}

/****************************************************************************/

Geometry::Point CPBox::getCenter () const
{
        // Zwracamy pusty, bo i tak Angle zawsze jest 0, a scale 1;
        return Geometry::Point ();
}

/****************************************************************************/

void CPBox::parentCallback (IModel *m)
{
        Body *b = static_cast <Body *> (m);
        shape = cpSpaceAddShape (Space::getSpace(), cpBoxShapeNew2 (b->getBody (),
                   cpBBNew (box.ll.x, box.ll.y, box.ur.x, box.ur.y)));
        cpShapeSetUserData (shape, this);

        // TODO można zrobic cast w zalezności od define DEBUG/RELEASE.
        Body *body = static_cast <Body *> (m);
        body->addInertia (cpMomentForBox (body->getMass (), getWidth (), getHeight ()));
        AbstractModel::parentCallback (m);
}


} /* namespace Model1 */
