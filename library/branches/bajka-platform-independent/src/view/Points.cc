/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Points.h"
#include "view/openGl/OpenGl.h"
#include "model/IVertexBufferEnabled.h"
#include "model/IModel.h"
#include "util/Exceptions.h"
#include "draw/Primitives.h"
#include "util/IShell.h"

namespace View {

void Points::update (Model::IModel *model, Event::UpdateEvent *, Util::IShell *shell)
{
        Model::IVertexBufferEnabled *array = dynamic_cast <Model::IVertexBufferEnabled *>  (model);
        assertThrow (array , "Points::update : !cB")

        DrawUtil::drawPoints (shell->getGLContext (), array->getVertexBuffer (), color, size);
}

} /* namespace View */
