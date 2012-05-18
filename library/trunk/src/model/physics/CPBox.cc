/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_CHIPMUNK
#include <chipmunk.h>
#include "CPBox.h"
#include "Body.h"
#include "Space.h"

namespace Model {

Geometry::Point CPBox::getTranslate () const
{
        return Geometry::Point ();
}

/****************************************************************************/

Geometry::Point CPBox::getCenter () const
{
        // Zwracamy pusty, bo i tak Angle zawsze jest 0, a scale 1;
        return Geometry::Point ();
}

/****************************************************************************/

void CPBox::onParentSet (IModel *m)
{
        Body *b = static_cast <Body *> (m);
        shape = cpSpaceAddShape (Space::getSpace(), cpBoxShapeNew2 (b->getBody (),
                   cpBBNew (box.ll.x, box.ll.y, box.ur.x, box.ur.y)));
        cpShapeSetUserData (shape, this);

        // TODO czy to powinna być masa całego body?
        b->addInertia (cpMomentForBox (b->getMass (), getWidth (), getHeight ()));
        AbstractModel::onParentSet (m);
}


} /* namespace Model1 */

#endif
