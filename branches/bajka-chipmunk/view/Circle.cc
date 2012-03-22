/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>
#include "draw/Primitives.h"
#include "../model/static/Circle.h"
#include "Circle.h"

namespace View {

void Circle::update (Model::IModel *model, Event::UpdateEvent *)
{
        Model::Circle *c = dynamic_cast <Model::Circle *>  (model);

        if (!c) {
                return;
        }

        // Obrót jest w preUpdate.
        DrawUtil::drawCircle (c->getOrigin (), 0, c->getRadius (), getForeground (), getBackground ());
}

} /* namespace View */
