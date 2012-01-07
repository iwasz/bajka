/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL.h>
#include <SDL_opengl.h>

#include "Rectangle.h"
#include "../model/Box.h"

namespace View {

void Rectangle::setModel (Ptr <Model::IModel> model)
{
        AbstractWidget::setModel (model);

        if (!model) {
                return;
        }

        box = dynamic_cast <Model::Box *> (model.get ());
        ASSERT (box, "dynamic_cast <Model2::Box2 *> (model.get ()) failed.");
}

/****************************************************************************/

void Rectangle::doDraw ()
{
        // TODO Do wywalenia.
        glColor3f (1.0, 0.0, 0.0);

        ASSERT (box, "No model @ Rectangle::doDraw. Model is required in Rectangle widget.");
        glBegin (GL_LINE_LOOP);
                glVertex2f (box->getX1 (), box->getY1 ());
                glVertex2f (box->getX1 (), box->getY2 ());
                glVertex2f (box->getX2 (), box->getY2 ());
                glVertex2f (box->getX2 (), box->getY1 ());
        glEnd ();
}

}
