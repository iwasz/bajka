/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "OpenGl.h"
#include "Widget.h"
#include "../model/IModel.h"

namespace View {

void Widget::preUpdate (Model::IModel *model, Event::UpdateEvent *)
{
        if (!visible) {
                return;
        }

        defaultPreUpdate (model);
}

/****************************************************************************/

void Widget::postUpdate (Model::IModel *model, Event::UpdateEvent *)
{
        if (!visible) {
                return;
        }

        defaultPostUpdate (model);
}

/****************************************************************************/

void Widget::defaultPreUpdate (Model::IModel *model)
{

        if (model) {
                glPushMatrix ();
//                glMultMatrixd (model->getMatrix ().data ().begin ());
                Geometry::Point c = model->getCenter ();
                Geometry::Point p = model->getTranslate ();

                glTranslatef (c.x + p.x, c.y + p.y, 0.0);
                glRotatef (model->getAngle(), 0.0, 0.0, 1.0); // angle * 180.0f / M_PI
                glScalef (model->getScale (), model->getScale (), 1.0);
                glTranslatef (-c.x, -c.y, 0.0);
        }
}

/****************************************************************************/

void Widget::defaultPostUpdate (Model::IModel *model)
{
        if (model) {
                glPopMatrix ();
        }
}

} /* namespace View */
