/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>
#include "DebugWidget.h"
#include "draw/Primitives.h"
#include "../model/static/Box.h"
#include "../view/draw/Primitives.h"
#include "../model/physics/CPBox.h"

using View::DrawUtil;

namespace Demo {
using namespace Geometry;

void DebugWidget::update (Model::IModel *model)
{
        Model::CPBox *c = dynamic_cast <Model::CPBox *>  (model);

        if (c) {
                DrawUtil::drawRectangle (c->getPosition(),
                                         Point (c->getPosition ().x + c->getWidth (), c->getPosition ().y + c->getHeight ()),
                                         getForeground (),
                                         getBackground ());
                return;
        }

        Model::Box *cB = dynamic_cast <Model::Box *>  (model);

        Geometry::Box const &b = cB->getBox ();

//        std::cout << "Przed" << b.toString() << std::endl;
        Point p1 = b.ll;
        cB->transform (&p1);
        Point p2 (b.ll.x, b.ur.y);
        cB->transform (&p2);
        Point p3 = b.ur;
        cB->transform (&p3);
        Point p4 (b.ur.x, b.ll.y);
        cB->transform (&p4);

//        std::cout << "Po" << b.toString() << std::endl;

//        DrawUtil::drawRectangle (b.ll,
//                                 b.ur,
//                                 getForeground (),
//                                 getBackground ());

        DrawUtil::drawLine (p1, p2, View::Color (0, 1, 0));
        DrawUtil::drawLine (p2, p3, View::Color (0, 1, 0));
        DrawUtil::drawLine (p3, p4, View::Color (0, 1, 0));
        DrawUtil::drawLine (p4, p1, View::Color (0, 1, 0));
//        DrawUtil::drawLine (p1, p3, View::Color (1, 0, 0));

        Geometry::Box aabb = model->getBoundingBox ();
        DrawUtil::drawRectangle (aabb,
                                 View::Color (1, 0, 0),
                                 View::Color (0, 0, 0, 0));

        std::cout << b.toString () << ", " << p1.toString() << ", " << p3.toString() << ", aabb=" << aabb.toString() << std::endl;
}

} /* namespace View */