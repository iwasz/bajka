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

namespace View {

void Primitive::update (Model::IModel *model, Event::UpdateEvent *)
{
        // TODO cast zależny od makra DEBUG
        Model::IPointArray *array = dynamic_cast <Model::IPointArray *>  (model);
        assertThrow (array , "Primitive::update : !cB")

        glVertexPointer (2, GL_FLOAT, 0, array->getPointArray ());

        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

        Color const &fill = getBackground ();
        if (fill.a > 0) {
                glColor4f (fill.r, fill.g, fill.b, fill.a);
                glDrawArrays (GL_TRIANGLE_FAN, 0, array->getNumberOfPoints ());
        }

        Color const &line = getForeground ();
        if (line.a > 0) {
                glColor4f (line.r, line.g, line.b, line.a);
                glDrawArrays (GL_LINE_LOOP, 0, array->getNumberOfPoints ());
        }
}

} /* namespace View */
