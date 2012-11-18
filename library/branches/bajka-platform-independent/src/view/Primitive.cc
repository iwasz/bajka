/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Primitive.h"
#include "view/openGl/OpenGl.h"
#include "model/IVertexBufferEnabled.h"
#include "model/IModel.h"
#include "util/Exceptions.h"
#include "view/draw/Primitives.h"
#include "util/IShell.h"

namespace View {

void Primitive::update (Model::IModel *model, Event::UpdateEvent *, Util::IShell *shell)
{
        Model::IVertexBufferEnabled *array = dynamic_cast <Model::IVertexBufferEnabled *>  (model);
        assertThrow (array , "Primitive::update : !cB")

        if (prettyJoin) {
                DrawUtil::drawSegmentsPrettyJoin (shell->getGLContext (), array->getVertexBuffer (), getForeground (), getBackground (), getThickness ());
        }
        else {
                DrawUtil::drawSegments (shell->getGLContext (), array->getVertexBuffer (), getForeground (), getBackground (), getThickness ());
        }
}

} /* namespace View */
