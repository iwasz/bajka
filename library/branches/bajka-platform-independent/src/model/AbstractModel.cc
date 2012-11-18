/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <algorithm>
#include <boost/bind.hpp>
#include "model/AbstractModel.h"
#include "model/Group.h"
#include "view/Widget.h"
#include "view/draw/Primitives.h"
#include "events/types/UpdateEvent.h"
#include "Platform.h"
#include "util/Config.h"
#include "util/IShell.h"
#include "view/draw/Primitives.h"

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

void AbstractModel::update (Event::UpdateEvent *e, Util::IShell *shell)
{
        if (controller && controller->getEventMask () & Event::UPDATE_EVENT) {
                controller->onPreUpdate (e, this, view);
                controller->onUpdate (e, this, view);
        }

        if (config ()->showAABB) {
                View::DrawUtil::drawAABB (shell->getGLContext (), this);
        }

        if (view) {
                view->preUpdate (this, e, shell);
                view->update (this, e, shell);
        }
        else {
        	View::Widget::defaultPreUpdate (this, shell);
        }

        if (isGroup ()) {
                IGroup *g = dynamic_cast <IGroup *> (this);
                std::for_each (g->begin (), g->end (), boost::bind (&IModel::update, _1, e, shell));
        }

        if (view) {
                view->postUpdate (this, e, shell);
        }
        else {
        	View::Widget::defaultPostUpdate (this, shell);
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
