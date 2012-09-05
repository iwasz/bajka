/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Points.h"
#include "OpenGl.h"
#include "IVertexBufferEnabled.h"
#include "IModel.h"
#include "../util/Exceptions.h"
#include "draw/Primitives.h"

namespace View {

void Points::update (Model::IModel *model, Event::UpdateEvent *)
{
        Model::IVertexBufferEnabled *array = dynamic_cast <Model::IVertexBufferEnabled *>  (model);
        assertThrow (array , "Points::update : !cB")

        DrawUtil::drawPoints (array->getVertexBuffer (), color, size);
}

} /* namespace View */
