/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <algorithm>
#include <boost/bind.hpp>
#include "AbstractModel.h"
#include "Group.h"
#include "BoxGroup.h"
#include "../view/Widget.h"
#include "../view/draw/Primitives.h"
#include "../events/types/UpdateEvent.h"
#include "../util/App.h"

namespace Model {
using View::DrawUtil;
using namespace Geometry;

Geometry::Point AbstractModel::getTranslate () const
{
        if (!layout) {
                return translate;
        }
        else {
                Point const &p = layout->getTranslateRel ();

                if (p.x < 0 || p.y < 0) {
                        return translate;
                }

                /*
                 * TODO Tu możnaby kiedyś zrobić optymalizację, że IModel ma metody getWidth i getHeight, które
                 * działają czybciej niż getBoundingBox. Tylko nie wiem, czy da się szybciej niż transformując
                 * punkty obiektu przez macierz?
                 */
                Geometry::Box aabb = getBoundingBoxImpl (AffineMatrix (Geometry::ZERO_POINT, getAngle (), getScale (), getCenter ()));
                return layout->calculateTranslation (this, translate, aabb.getWidth (), aabb.getHeight ());
        }
}

/****************************************************************************/

void AbstractModel::setTranslate (Geometry::Point const &p)
{
        translate = p;

        if (layout) {
                layout->resetTranslateRel ();
        }
}

/****************************************************************************/

AffineMatrix AbstractModel::getMatrix () const
{
        return AffineMatrix (getTranslate (), getAngle (), getScale (), getCenter ());
}

/****************************************************************************/

Geometry::Point AbstractModel::getCenter () const
{
        if (center.get ()) {
                return *center;
        }

        return computeCenter ();
}

/****************************************************************************/

void AbstractModel::setCenter (Geometry::Point const &p)
{
        if (!center.get ()) {
                center = std::auto_ptr <Geometry::Point> (new Geometry::Point (p));
        }
        else {
                *center = p;
        }
}

/****************************************************************************/

void AbstractModel::update (Event::UpdateEvent *e)
{
        if (controller && controller->getEventMask () & Event::UPDATE_EVENT) {
                controller->onPreUpdate (e, this, view);
                controller->onUpdate (e, this, view);
        }

#ifndef ANDROID // TODO wyrzucić.
        if (config ()->getShowAABB ()) {
                Geometry::Box aabb= getBoundingBox();

                if (aabb.getHeight() && aabb.getHeight()) {
                        DrawUtil::drawRectangle (aabb, View::Color::RED, View::Color::TRANSPARENT);
                }
        }
#endif

        if (view) {
                view->preUpdate (this, e);
                view->update (this, e);
        }
        else {
        	View::Widget::defaultPreUpdate (this);
        }

        if (isGroup ()) {
                IGroup *g = dynamic_cast <IGroup *> (this);
                std::for_each (g->begin (), g->end (), boost::bind (&IModel::update, _1, e));
        }

        if (view) {
                view->postUpdate (this, e);
        }
        else {
        	View::Widget::defaultPostUpdate (this);
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
