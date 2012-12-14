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

namespace View {

void Primitive::update (Model::IModel *model, Event::UpdateEvent *, View::GLContext *ctx)
{
//        Model::IVertexBufferEnabled *array = dynamic_cast <Model::IVertexBufferEnabled *>  (model);
//        assertThrow (array , "Primitive::update : !cB")
//
//        if (prettyJoin) {
//                DrawUtil::drawSegmentsPrettyJoin (ctx, array->getVertexBuffer (), getForeground (), getBackground (), getThickness ());
//        }
//        else {
//                DrawUtil::drawSegments (ctx, array->getVertexBuffer (), getForeground (), getBackground (), getThickness ());
//        }
}

} /* namespace View */
