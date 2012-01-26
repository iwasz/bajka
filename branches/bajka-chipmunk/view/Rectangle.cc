/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>
#include "../model/Box.h"
#include "Rectangle.h"
#include "draw/Primitives.h"
#include "../model/static/BoxB.h"

namespace View {
using namespace Geometry;

void Rectangle::update (Model::IModel *model)
{
//        Model::Box *c = static_cast <Model::Box *>  (model);

// TODO wywalić!
        Model::Box *c = dynamic_cast <Model::Box *>  (model);

        if (c) {
                DrawUtil::drawRectangle (c->getPosition(),
                                         Point (c->getPosition ().x + c->getWidth (), c->getPosition ().y + c->getHeight ()),
                                         getForeground (),
                                         getBackground ());
                return;
        }

        Model::BoxB *cB = dynamic_cast <Model::BoxB *>  (model);

        Geometry::Box const &b = cB->getBox ();
        DrawUtil::drawRectangle (b.ll,
                                 b.ur,
                                 getForeground (),
                                 getBackground ());


}

} /* namespace View */
