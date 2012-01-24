/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>
#include "Widget.h"
#include "../model/IModel.h"

namespace View {

void Widget::preUpdate (Model::IModel *model)
{
        if (!visible) {
                return;
        }

        defaultPreUpdate (model);
}

/****************************************************************************/

void Widget::postUpdate (Model::IModel *model)
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
            Geometry::Point c = model->getCenter ();
            Geometry::Point p = model->getPosition ();

            glTranslated (c.x, c.y, 0.0);
            glRotated (model->getAngle(), 0.0, 0.0, 1.0); // angle * 180.0f / M_PI
            glScaled (model->getScale (), model->getScale (), 0.0);
            glTranslated (-c.x + p.x, -c.y + p.y, 0.0f);
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
