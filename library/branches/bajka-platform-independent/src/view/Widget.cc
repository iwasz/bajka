/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "view/openGl/OpenGl.h"
#include "view/Widget.h"
#include "model/IModel.h"
#include "Platform.h"
#include "util/Config.h"
#include "draw/Primitives.h"
#include "util/IShell.h"

namespace View {

void Widget::preUpdate (Model::IModel *model, Event::UpdateEvent *)
{
        if (!visible) {
                return;
        }

        defaultPreUpdate (model, NULL);
}

/****************************************************************************/

void Widget::postUpdate (Model::IModel *model, Event::UpdateEvent *)
{
        if (!visible) {
                return;
        }

        defaultPostUpdate (model, NULL);
}

/****************************************************************************/

void Widget::defaultPreUpdate (Model::IModel *model, Util::IShell *shell)
{
        if (model) {
                glMatrixMode (GL_MODELVIEW);
                glPushMatrix ();
                Geometry::Point c = model->getRotationCenter ();
                Geometry::Point p = model->getTranslate ();

#if 0
                std::cerr << typeid (*model).name () << " : tran=" << p << ", cent=" << c << std::endl;
#endif

                glTranslatef (c.x + p.x, c.y + p.y, 0.0);
                glRotatef (model->getAngle(), 0.0, 0.0, 1.0); // angle * 180.0f / M_PI
                glScalef (model->getScale (), model->getScale (), 1.0);
                glTranslatef (-c.x, -c.y, 0.0);
        }
}

/****************************************************************************/

void Widget::defaultPostUpdate (Model::IModel *model, Util::IShell *shell)
{
        if (model) {
                glMatrixMode (GL_MODELVIEW);
                glPopMatrix ();
        }
}

/****************************************************************************/

void Widget::drawAABB (Model::IModel *model)
{
        if (model && config ()->showAABB) {
                Geometry::Box aabb = model->getBoundingBox();

#if 0
                std::cerr << typeid (*model).name () << " : aabb=" << aabb << std::endl;
#endif

                if (aabb.getWidth () && aabb.getHeight ()) {
                        DrawUtil::drawRectangle (aabb, View::Color::RED, View::Color::TRANSPARENT);
                }
        }
}

} /* namespace View */
