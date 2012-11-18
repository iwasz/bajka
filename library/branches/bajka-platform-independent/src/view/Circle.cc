/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "draw/Primitives.h"
#include "model/static/Circle.h"
#include "Circle.h"
#include "util/IShell.h"

namespace View {

void Circle::update (Model::IModel *model, Event::UpdateEvent *, Util::IShell *shell)
{
        Model::Circle *c = dynamic_cast <Model::Circle *>  (model);
        DrawUtil::drawCircle (shell->getGLContext (), c->getOrigin (), 0, c->getRadius (), getForeground (), getBackground (), getThickness ());
}

} /* namespace View */
