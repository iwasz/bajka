/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_GEOM_POINT3_H_
#define BAJKA_GEOM_POINT3_H_

#include <string>
#include <core/variant/Variant.h>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_copy.hpp>
#include <boost/type_traits/is_pod.hpp>

namespace Geometry {

struct Point3 {
        float x, y, z;
};

BOOST_STATIC_ASSERT (boost::has_trivial_assign <Point3>::value);
BOOST_STATIC_ASSERT (boost::has_trivial_copy <Point3>::value);
BOOST_STATIC_ASSERT (boost::is_pod <Point3>::value);

/**
 * Tworzy punkt z reprezentacji napisowej.
 */
extern Point3 stringToPoint2 (std::string const &p);

/**
 * Tworzy punkt z reprezentacji napisowej, zwraca jako Core::Variant.
 */
extern Core::Variant stringToPoint3Variant (std::string const &p);

} // nam

#endif /* POINT3_H_ */
