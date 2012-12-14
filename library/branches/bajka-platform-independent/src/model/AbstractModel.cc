/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <algorithm>
#include "model/AbstractModel.h"
#include "model/Group.h"
#include "view/Widget.h"
#include "view/draw/Primitives.h"
#include "events/types/UpdateEvent.h"
#include "Platform.h"
#include "util/Config.h"
#include "view/draw/Primitives.h"
#include "util/UpdateContext.h"

namespace Model {
using namespace Geometry;

/****************************************************************************/

AffineMatrix AbstractModel::getMatrix () const
{
        return AffineMatrix (getTranslate (), getAngle (), getScale (), getRotationCenter ());
}

/****************************************************************************/

Geometry::Point AbstractModel::getRotationCenter () const
{
        if (center.get ()) {
                return *center;
        }

        return computeCenter ();
}

/****************************************************************************/

void AbstractModel::setRotationCenter (Geometry::Point const &p)
{
        if (!center.get ()) {
                center = std::auto_ptr <Geometry::Point> (new Geometry::Point (p));
        }
        else {
                *center = p;
        }
}

/****************************************************************************/

void AbstractModel::update (Event::UpdateEvent *e, Util::UpdateContext *uCtx)
{
        if (controller && controller->getEventMask () & Event::UPDATE_EVENT) {
                controller->onPreUpdate (e, this, view);
                controller->onUpdate (e, this, view);
        }

        View::GLContext *glContext = uCtx->glContext;

        if (config ()->showAABB) {
                View::DrawUtil::drawAABB (glContext, this);
        }

        if (view) {
                view->preUpdate (this, e, glContext);
                view->update (this, e, glContext);
        }
        else {
        	View::Widget::defaultPreUpdate (this, glContext);
        }

        if (isGroup ()) {
                IGroup *g = dynamic_cast <IGroup *> (this);

                // Call stack of this was hilarous.
                // std::for_each (g->begin (), g->end (), boost::bind (&IModel::update, _1, e, shell));

                for (ModelVector::iterator i = g->begin (); i != g->end (); ++i) {
                        (*i)->update (e, uCtx);
                }
        }

        if (view) {
                view->postUpdate (this, e, glContext);
        }
        else {
        	View::Widget::defaultPostUpdate (this, glContext);
        }

        if (controller && controller->getEventMask () & Event::UPDATE_EVENT) {
                controller->onPostUpdate (e, this, view);
        }
}

/****************************************************************************/

IModel *AbstractModel::findContains (Geometry::Point const &p)
{
        Geometry::Box aabb = getBoundingBox ();

        if (!aabb.contains (p)) {
                return NULL;
        }

        if (!this->contains (p)) {
                return NULL;
        }

        return this;
}

} /* namespace Model1 */
