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
#include "../model/Box.h"

namespace View {
using namespace Geometry;

void Rectangle::update (Model::IModel *model)
{
        Model::Box *c = static_cast <Model::Box *>  (model);
        DrawUtil::drawRectangle (c->getPosition(),
                                 Point (c->getPosition ().x + c->getWidth (), c->getPosition ().y + c->getHeight ()),
                                 Color (),
                                 Color (0, 0, 1));
}

} /* namespace View */
