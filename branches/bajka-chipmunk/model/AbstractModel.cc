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
#include "../util/BajkaApp.h"

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
                Geometry::Box aabb = getBoundingBoxImpl (AffineMatrix (Point (0, 0), getAngle (), getScale (), getCenter ()));
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

void AbstractModel::update ()
{
        if (controller) {
                controller->preUpdate (this, view);
                controller->update (this, view);
        }

        if (config ()->getShowAABB ()) {
                Geometry::Box aabb= getBoundingBox();

                if (aabb.getHeight() && aabb.getHeight()) {
                        DrawUtil::drawRectangle (aabb, View::Color::RED, View::Color::TRANSPARENT);
                }
        }

        if (view) {
                view->preUpdate (this);
                view->update (this);
        }
        else {
        	View::Widget::defaultPreUpdate (this);
        }

        if (isGroup ()) {
        		IGroup *g = dynamic_cast <IGroup *> (this);
        		std::for_each (g->begin (), g->end (), boost::mem_fn (&IModel::update));
        }

        if (view) {
                view->postUpdate (this);
        }
        else {
        	View::Widget::defaultPostUpdate (this);
        }

        if (controller) {
                controller->postUpdate (this, view);
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

/****************************************************************************/

//void AbstractModel::setTranslateRel (Geometry::Point const &t)
//{
//        BoxGroup *parGroup = getParGroup ();
//        relativeTranslation = true;
//
//        if (!parGroup) {
//                translate = t;
//                return;
//        }
//
//        // Przypadek domyślny - nie pobieramy aabb
//        if (align == (TOP | RIGHT)) {
//                setTranslate (Point (parGroup->getWidth() * t.x / 100.0, parGroup->getHeight () * t.y / 100.0));
//        }
//        else {
//                Geometry::Box aabb = getBoundingBox ();
//                Geometry::Point ct = Point (parGroup->getWidth() * t.x / 100.0, parGroup->getHeight () * t.y / 100.0);
//
//                if (align & HCENTER) {
//                        ct.x -= aabb.getWidth () / 2.0;
//                }
//                else if (align & LEFT) {
//                        ct.x -= aabb.getWidth ();
//                }
//
//                if (align & VCENTER) {
//                        ct.y -= aabb.getHeight () / 2.0;
//                }
//                else if (align & BOTTOM) {
//                        ct.y -= aabb.getHeight ();
//                }
//
//                setTranslate (ct);
//        }
//}

/****************************************************************************/

//void AbstractModel::onParentSet (IModel *m)
//{
////        // Uruchamiamy jeszcze raz, bo teraz mamy parenta (ułatwoenie dla kontenera).
////        if (relativeTranslation) {
////                setTranslateRel (translate);
////        }
//}

} /* namespace Model1 */
