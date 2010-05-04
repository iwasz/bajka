/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 22, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>
#include "AbstractWidget.h"

namespace View {

void AbstractWidget::setModel (Ptr <Model::IModel> m)
{
        model = dynamic_pointer_cast <Model::Item> (m);
        assert (model);
}

void AbstractWidget::doTransform ()
{
        if (!model) {
                // TODO nie wiem, czy to ma być sytuacja wyjątkowa.
                throw 667;
        }

        glTranslated (model->getTranslatePoint ().getX () + model->getCenter ().getX (),
                        model->getTranslatePoint ().getY () + model->getCenter ().getY (), 0.0);
        glRotated (model->getRotateAngle (), 0.0, 0.0, 1.0);
        glTranslated (-model->getCenter ().getX (), -model->getCenter ().getY (), 0.0);
        glScaled (model->getScaleW (), model->getScaleH (), 1.0);
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
