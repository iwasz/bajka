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

void Widget::postUpdate (Model::IModel *model)
{
        if (!visible) {
                return;
        }

        defaultPostUpdate (model);
}

void Widget::defaultPreUpdate (Model::IModel *model)
{
    glPushMatrix ();

    if (model) {
            glTranslatef (model->getPosition().x, model->getPosition().y, 0.0f);
//                glRotatef (angle*180.0f/M_PI, 0.0f, 0.0f, 1.0f);
            glRotatef (model->getAngle(), 0.0f, 0.0f, 1.0f);
    }
}

void Widget::defaultPostUpdate (Model::IModel *)
{
    glPopMatrix ();
}

} /* namespace View */
