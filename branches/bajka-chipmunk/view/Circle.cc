/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>
#include "Circle.h"
#include "../model/IModel.h"
#include "../model/Circle.h"
#include "draw/Primitives.h"

namespace View {

void Circle::update (Model::IModel *model)
{
        Model::Circle *c = static_cast <Model::Circle *>  (model);
        DrawUtil::drawCircle (c->getPosition(), c->getAngle (), c->getRadius (), Color (), Color (0, 0, 1));
}

} /* namespace View */
