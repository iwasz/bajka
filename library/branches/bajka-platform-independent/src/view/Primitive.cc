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

        if (prettyJoin) {
                DrawUtil::drawSegmentsPrettyJoin (array->getVertexBuffer (), getForeground (), getBackground (), getThickness ());
        }
        else {
                DrawUtil::drawSegments (array->getVertexBuffer (), getForeground (), getBackground (), getThickness ());
        }
}

} /* namespace View */
