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

        glPushMatrix ();

        if (model) {
                glMultMatrixd (model->getMatrix ());
        }
}

//void Widget::update (Model::IModel *model)
//{
//
//}

void Widget::postUpdate (Model::IModel *model)
{
        if (!visible) {
                return;
        }

        glPopMatrix ();
}

} /* namespace View */
