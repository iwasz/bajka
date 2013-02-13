/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DELAUNAYPOINT_H_
#define DELAUNAYPOINT_H_

#include <boost/polygon/isotropy.hpp>
#include <boost/math/special_functions/round.hpp>

namespace Delaunay {

/**
 *
 */
enum PointCoordinate { X = 1, Y = 2 };

/**
 * Defaul Point class. It is assumed that user has his own implementation, thus this class
 * is provided only for saske of completeness.
 */
struct Point {
        typedef float CoordinateType;

        Point (CoordinateType x_ = 0, CoordinateType y_ = 0) : x (x_), y (y_)  {}
        CoordinateType x, y;

        inline CoordinateType get (PointCoordinate s) const
        {
                return ((s == X) ? (x) : (y));
        }

        inline void set (PointCoordinate s, CoordinateType v)
        {
                if (s == X) {
                        x = v;
                }
                else {
                        y = v;
                }
        }
};


template<typename T>
struct PointTraits {
        typedef typename T::CoordinateType CoordinateType;
        typedef int IntCoordinateType;

        static inline CoordinateType get (const T& point, PointCoordinate orient)
        {
                return point.get (orient);
        }

        static inline IntCoordinateType get (const T& point, boost::polygon::orientation_2d orient)
        {
                return (orient == boost::polygon::HORIZONTAL) ? boost::math::iround (get (point, X)) : boost::math::iround (get (point, Y));
        }

};

template<typename T>
struct PointMutableTraits {
        typedef typename PointTraits <T>::CoordinateType CoordinateType;

        static inline void set (const T& point, PointCoordinate orient, CoordinateType c)
        {
                return point.set (orient, c);
        }


        /**
         * Zero initialized point.
         */
        static inline T construct (CoordinateType x = 0, CoordinateType y = 0)
        {
                return T (x, y);
        }
};

/**
 * Helper accessor.
 */
template <typename T>
typename PointTraits <T>::CoordinateType x (T const &point)
{
        return PointTraits <T>::get (point, X);
}

/**
 * Helper accessor.
 */
template <typename T>
void x (T const &point, typename PointTraits <T>::CoordinateType p)
{
        PointMutableTraits <T>::set (point, X, p);
}

/**
 * Helper accessor.
 */
template <typename T>
typename PointTraits <T>::CoordinateType y (T const &point)
{
        return PointTraits <T>::get (point, Y);
}

/**
 * Helper accessor.
 */
template <typename T>
void y (T const &point, typename PointTraits <T>::CoordinateType p)
{
        PointMutableTraits <T>::set (point, Y, p);
}

} // namespace Delaunay

#endif /* DELAUNAYPOINT_H_ */
