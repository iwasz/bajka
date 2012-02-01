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

void AbstractModel::initMatrix ()
{
	if (!matrix.get ()) {
		matrix = std::auto_ptr <Geometry::AffineMatrix> (new Geometry::AffineMatrix ());
	}
}

/****************************************************************************/

Geometry::AffineMatrix const &AbstractModel::getMatrix () const
{
	if (!matrix.get ()) {
		return Geometry::AffineMatrix::UNITARY;
	}

	return *matrix;
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

Geometry::Point AbstractModel::getTranslate () const
{
	if (!matrix.get ()) {
		return Point ();
	}

    return Point (matrix->operator () (0,3), matrix->operator () (1,3));
}

/****************************************************************************/

void AbstractModel::setTranslate (Geometry::Point const &p)
{
	initMatrix ();
	matrix->move (p);
}

/****************************************************************************/

double AbstractModel::getAngle () const
{
	if (!matrix.get ()) {
		return 0;
	}

	// TODO, czy nie da się jakoś łatwiej?
    Point p (1.0, 0.0);
    double tmpX = matrix->operator () (0,3);
    double tmpY = matrix->operator () (1,3);
    AbstractModel *ptr = const_cast <AbstractModel *> (this);
    ptr->matrix->operator () (0,3) = 0.0;
    ptr->matrix->operator () (1,3) = 0.0;
    matrix->transform (&p);
    ptr->matrix->operator () (0,3) = tmpX;
    ptr->matrix->operator () (1,3) = tmpY;
    double ret = atan2 (p.x, p.x) * (180.0 / M_PI);
    return (ret < 0) ? (ret + 360) : ret;
}

/****************************************************************************/

void AbstractModel::setAngle (double a)
{
	initMatrix ();
	matrix->rotate (a * M_PI / 180.0, getCenter ());
}

/****************************************************************************/

double AbstractModel::getScale () const
{
	if (!matrix.get ()) {
		return 1;
	}

	// TODO, czy nie da się jakoś łatwiej?
    Point p (1.0, 0.0);
    double tmpX = matrix->operator () (0,3);
    double tmpY = matrix->operator () (1,3);
    AbstractModel *ptr = const_cast <AbstractModel *> (this);
    ptr->matrix->operator () (0,3) = 0.0;
    ptr->matrix->operator () (1,3) = 0.0;
    matrix->transform (&p);
    ptr->matrix->operator () (0,3) = tmpX;
    ptr->matrix->operator () (1,3) = tmpY;
    return p.x;
}

/****************************************************************************/

void AbstractModel::setScale (double s)
{
	initMatrix ();
	matrix->resize (s, s, getCenter ());
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
        		Group *g = static_cast <Group *> (this);
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

void AbstractModel::transform (Geometry::Point *p) const
{
//        double aRad = angle * M_PI / 180.0;
//        // Pomnożyć sin i cos razy scale i podstawić.
//        double s = sin (aRad);
//        double c = cos (aRad);
//        double x = p->x;
//        Geometry::Point ct = getCenter ();
//
//        p->x = scale * c * (x - scale * ct.x) + scale * s * (scale * ct.y - p->y) + ct.x + translate.x;
//        p->y = scale * c * (p->y - scale * ct.y) + scale * s * (x - scale * ct.x) + ct.y + translate.y;
	getMatrix ().transform (p);
}

} /* namespace Model1 */
