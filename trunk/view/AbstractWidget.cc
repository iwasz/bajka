/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>
#include "AbstractWidget.h"

namespace View {

void AbstractWidget::doTransform ()
{
        if (model) {
                glMultMatrixd (model->getMatrix ().data ().begin ());
        }
}

void AbstractWidget::preDraw ()
{
        glPushMatrix ();
}

void AbstractWidget::postDraw ()
{
        glPopMatrix ();
}

}
