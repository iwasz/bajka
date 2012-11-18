/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Rectangle.h"
#include "draw/Primitives.h"
#include "model/static/Box.h"
#include "model/physics/CPBox.h"
#include "util/Exceptions.h"
#include "view/openGl/OpenGl.h"
#include "util/IShell.h"

namespace View {
using namespace Geometry;

void Rectangle::update (Model::IModel *model, Event::UpdateEvent *, Util::IShell *shell)
{
        Model::IBox *cB = dynamic_cast <Model::IBox *>  (model);
        assertThrow (cB, "Rectangle::update : !cB")
        Geometry::Box const &b = cB->getBox ();

        DrawUtil::drawRectangle (shell->getGLContext (),
                                 b.ll,
                                 b.ur,
                                 getForeground (),
                                 getBackground (),
                                 getThickness ());
}

} /* namespace View */
