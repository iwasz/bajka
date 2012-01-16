/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>
#include "../model/Circle.h"
#include "../model/IModel.h"
#include "draw/Primitives.h"
#include "Circle.h"

namespace View {

void Circle::update (Model::IModel *model)
{
        Model::Circle *c = static_cast <Model::Circle *>  (model);
        // Obrót jest w preUpdate.
        DrawUtil::drawCircle (c->getPosition(), 0, c->getRadius (), getForeground (), getBackground ());
}

} /* namespace View */
