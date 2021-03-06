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

namespace View {

void Points::update (Model::IModel *model, Event::UpdateEvent *, View::GLContext *ctx)
{
//        Model::IVertexBufferEnabled *array = dynamic_cast <Model::IVertexBufferEnabled *>  (model);
//        assertThrow (array , "Points::update : !cB")
//        DrawUtil::drawPoints (ctx, array->getVertexBuffer (), color, size);
}

} /* namespace View */
