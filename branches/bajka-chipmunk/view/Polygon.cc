/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>
#include "Polygon.h"
#include "../model/Box.h"
#include "../view/draw/Primitives.h"

namespace View {

void Rectangle::update (Model::IModel *model)
{
        // TODO Do wywalenia.
        glColor3f (1.0, 0.0, 0.0);

        // TODO Lub dynamic, dio zastanowienia się.
        // TODO Kastować na ogólniejszy typ.
        Model::Box *box = static_cast <Model::Box *> (model);

        double x = box->getPosition ().getX ();
        double y = box->getPosition ().getY ();

        glBegin (GL_LINE_LOOP);
                glVertex2f (x, y);
                glVertex2f (x, y + box->getHeight ());
                glVertex2f (x + box->getHeight (), y + box->getHeight ());
                glVertex2f (x + box->getHeight (), y);
        glEnd ();

//        View::DrawUtil::drawCircle (Geometry::Point (0, 0), 0, 50, View::Color (), View::Color (1, 0, 0));
        View::DrawUtil::drawLine (Geometry::Point (0, 0), Geometry::Point (100, 100), View::Color (1, 0, 0));

}

} /* namespace View */
