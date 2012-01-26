/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>
#include "Rectangle.h"
#include "draw/Primitives.h"
#include "../model/static/Box.h"
#include "../model/physics/CPBox.h"

namespace View {
using namespace Geometry;

void Rectangle::update (Model::IModel *model)
{
//        Model::CPBox *c = static_cast <Model::CPBox *>  (model);

// TODO wywalić!
        Model::CPBox *c = dynamic_cast <Model::CPBox *>  (model);

        if (c) {
                DrawUtil::drawRectangle (c->getPosition(),
                                         Point (c->getPosition ().x + c->getWidth (), c->getPosition ().y + c->getHeight ()),
                                         getForeground (),
                                         getBackground ());
                return;
        }

        Model::Box *cB = dynamic_cast <Model::Box *>  (model);

        Geometry::Box const &b = cB->getBox ();
        DrawUtil::drawRectangle (b.ll,
                                 b.ur,
                                 getForeground (),
                                 getBackground ());


}

} /* namespace View */
