#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cassert>

#include "../geometry/AffineMatrix.h"

BOOST_AUTO_TEST_SUITE (AffineMatrixTest);
using namespace Geometry;

/// TODO
BOOST_AUTO_TEST_CASE (testBasic)
{
        Geometry::AffineMatrix m;
        // Pi / 4
        m.rotate (0.7853981);
//        std::cerr << m.toString () << std::endl;

        Geometry::AffineMatrix m2 = m;
        m2.inverse ();
//        std::cerr << m2.toString () << std::endl;

        Geometry::AffineMatrix m3 = prod (m, m2);
//        std::cerr << m3.toString () << std::endl;


        Point p1 (-50, -50);
        Point p2 (50, 50);

        m.transform (&p1);
        m.transform (&p2);

//        std::cerr << p1.toString () << ", " << p2.toString () << std::endl;
}
 
BOOST_AUTO_TEST_SUITE_END ();
