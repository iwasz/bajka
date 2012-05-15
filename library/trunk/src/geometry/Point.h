/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MODEL2_POINT_H_
#define MODEL2_POINT_H_

#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <string>
#include <variant/Variant.h>

/**
 * Prymitywy geometryczne.
 */
namespace Geometry {

/**
 * Punkt.
 * \ingroup Geometry
 */
struct Point {

        float x;
        float y;
};

BOOST_STATIC_ASSERT (boost::has_trivial_assign <Point>::value);
BOOST_STATIC_ASSERT (boost::has_trivial_copy <Point>::value);
BOOST_STATIC_ASSERT (boost::is_pod <Point>::value);

/**
 * Wyrzucanie pinktu do strumienia.
 * \ingroup Geometry
 */
extern std::ostream &operator<< (std::ostream &o, Geometry::Point const &p);
extern std::string toString (Geometry::Point const &p);

/**
 * Początek układu współrzednych - stała.
 */
const Point ZERO_POINT = {0, 0};

/**
 * Tworzy punkt.
 */
static inline Point makePoint (float x, float y)
{
        Point p = {x, y};
        return p;
}

/**
 * Zwraca początek układu współrzędnych.
 */
static inline Point makePoint ()
{
        return ZERO_POINT;
}

/**
 * Tworzy punkt z reprezentacji napisowej.
 */
extern Point stringToPoint (std::string const &p);

/**
 * Tworzy punkt z reprezentacji napisowej, zwraca jako Core::Variant.
 */
extern Core::Variant stringToPointVariant (std::string const &p);

} // namespace

/*
 * Register my custom point Type.
 */
BOOST_GEOMETRY_REGISTER_POINT_2D (Geometry::Point, double, cs::cartesian, x, y)

#	endif /* POINT_H_ */
