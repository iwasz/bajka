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
        // TODO CAst zależny od makra DEBUG
        Model::IBox *cB = dynamic_cast <Model::IBox *>  (model);
        assertThrow (cB, "Rectangle::update : !cB")
        Geometry::Box const &b = cB->getBox ();
        DrawUtil::drawRectangle (b.ll,
                                 b.ur,
                                 getForeground (),
                                 getBackground ());


}

} /* namespace View */
