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

void Widget::preUpdate (Model::IModel *model, Event::UpdateEvent *, Util::IShell *shell)
{
        if (!visible) {
                return;
        }

        defaultPreUpdate (model, shell);
}

/****************************************************************************/

void Widget::postUpdate (Model::IModel *model, Event::UpdateEvent *, Util::IShell *shell)
{
        if (!visible) {
                return;
        }

        defaultPostUpdate (model, shell);
}

/****************************************************************************/

void Widget::defaultPreUpdate (Model::IModel *model, Util::IShell *shell)
{
        if (model) {
//                std::cerr << " " << model->getMatrix ().toString() << std::endl;
//                Geometry::AffineMatrix const &top = shell->getGLContext ()->pushMatrix (model->getMatrix ());
//                std::cerr << top.toString() << std::endl;
//                glMatrixMode (GL_MODELVIEW);
//                glLoadIdentity ();
//                // TODO glMultMatrixf
//                glMultMatrixd (top.data ().begin ());

                glMatrixMode (GL_MODELVIEW);
                glPushMatrix ();
//                Geometry::AffineMatrix top = model->getMatrix ();
//                glMultMatrixd (top.data ().begin ());

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
//                shell->getGLContext ()->popMatrix ();
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
