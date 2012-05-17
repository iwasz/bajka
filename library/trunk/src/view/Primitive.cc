/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Primitive.h"
#include "OpenGl.h"
#include "../model/IPointArray.h"
#include "../model/IModel.h"
#include "../util/Exceptions.h"
#include "draw/Primitives.h"

namespace View {

void Primitive::update (Model::IModel *model, Event::UpdateEvent *)
{
        Model::IPointArray *array = dynamic_cast <Model::IPointArray *>  (model);
        assertThrow (array , "Primitive::update : !cB")

        if (prettyJoin) {
                DrawUtil::drawSegmentsPrettyJoin (array->getPointArray (), array->getNumberOfPoints (), getForeground (), getBackground (), getThickness ());
        }
        else {
                DrawUtil::drawSegments (array->getPointArray (), array->getNumberOfPoints (), getForeground (), getBackground (), getThickness ());
        }
}

} /* namespace View */
