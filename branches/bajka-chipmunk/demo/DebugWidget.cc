/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL_opengl.h>
#include "../model/Box.h"
#include "DebugWidget.h"
#include "draw/Primitives.h"
#include "../model/basic/BoxB.h"
#include "../view/draw/Primitives.h"

using View::DrawUtil;

namespace Demo {
using namespace Geometry;

void DebugWidget::update (Model::IModel *model)
{
        Model::Box *c = dynamic_cast <Model::Box *>  (model);

        if (c) {
                DrawUtil::drawRectangle (c->getPosition(),
                                         Point (c->getPosition ().x + c->getWidth (), c->getPosition ().y + c->getHeight ()),
                                         getForeground (),
                                         getBackground ());
                return;
        }

        Model::BoxB *cB = dynamic_cast <Model::BoxB *>  (model);

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
        std::cout << p1.toString() << ", " << p2.toString()<< std::endl;

//        DrawUtil::drawRectangle (b.ll,
//                                 b.ur,
//                                 getForeground (),
//                                 getBackground ());

        DrawUtil::drawLine (p1, p2, View::Color (1, 0, 0));
        DrawUtil::drawLine (p2, p3, View::Color (1, 0, 0));
        DrawUtil::drawLine (p3, p4, View::Color (1, 0, 0));
        DrawUtil::drawLine (p4, p1, View::Color (1, 0, 0));


}

} /* namespace View */
