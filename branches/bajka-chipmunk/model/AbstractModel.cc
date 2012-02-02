/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "AbstractModel.h"
#include "../view/Widget.h"
#include <algorithm>
#include <boost/bind.hpp>
#include "../view/draw/Primitives.h"
#include "Group.h"

namespace Model {
using View::DrawUtil;
using namespace Geometry;

/****************************************************************************/

AffineMatrix AbstractModel::getMatrix () const
{
	return AffineMatrix (translate, angle, scale, getCenter ());
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

#if 1
        Geometry::Box aabb= getBoundingBox();

        if (aabb.getHeight() && aabb.getHeight()) {
        	DrawUtil::drawRectangle (aabb, View::Color::RED, View::Color::TRANSPARENT);
        }
#endif

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

//void AbstractModel::transform (Geometry::Point *p) const
//{
////        double aRad = angle * M_PI / 180.0;
////        // Pomnożyć sin i cos razy scale i podstawić.
////        double s = sin (aRad);
////        double c = cos (aRad);
////        double x = p->x;
////        Geometry::Point ct = getCenter ();
////
////        p->x = scale * c * (x - scale * ct.x) + scale * s * (scale * ct.y - p->y) + ct.x + translate.x;
////        p->y = scale * c * (p->y - scale * ct.y) + scale * s * (x - scale * ct.x) + ct.y + translate.y;
//	getMatrix ().transform (p);
//}

} /* namespace Model1 */
