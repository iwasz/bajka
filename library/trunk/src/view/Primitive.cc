/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Primitive.h"
#include "OpenGl.h"
#include "IVertexBufferEnabled.h"
#include "IModel.h"
#include "../util/Exceptions.h"
#include "draw/Primitives.h"

namespace View {

void Primitive::update (Model::IModel *model, Event::UpdateEvent *)
{
        Model::IVertexBufferEnabled *array = dynamic_cast <Model::IVertexBufferEnabled *>  (model);
        assertThrow (array , "Primitive::update : !cB")
        Model::VertexBuffer buffer = array->getVertexBuffer ();


        if (prettyJoin) {
                DrawUtil::drawSegmentsPrettyJoin (buffer.buffer, buffer.numVertices, buffer.stride, getForeground (), getBackground (), getThickness ());
        }
        else {
                DrawUtil::drawSegments (buffer.buffer, buffer.numVertices, buffer.stride, getForeground (), getBackground (), getThickness ());
        }
}

} /* namespace View */
