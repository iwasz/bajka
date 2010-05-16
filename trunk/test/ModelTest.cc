#include <boost/test/unit_test.hpp>
#include <sstream>
#include <boost/geometry/geometry.hpp>


#include "geometry/Geometry.h"
#include "IModel.h"

using namespace boost;
using namespace boost::geometry;

using namespace Model2;

BOOST_AUTO_TEST_SUITE (ModelTest);

/**
 *
 */
BOOST_AUTO_TEST_CASE (testPoint)
{
        {
                Point p (1.2, 3.4);
                BOOST_CHECK (p.toString () == "Point (1.2, 3.4)");
        }

/*--------------------------------------------------------------------------*/

        {
                Point p01 (1.2, 3.4);
                Point p02 (3.4, 1.2);
                p02 += p01;
                BOOST_CHECK (p02 == Point (4.6, 4.6));
        }

/*--------------------------------------------------------------------------*/

        {
                Point p01 (1.2, 3.4);
                Point p02 (3.4, 1.2);
                Point p = p02 + p01;
                BOOST_CHECK (p == Point (4.6, 4.6));
        }
}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testBox)
{
        {
                Box box (-10, 10, 10, -10);
                BOOST_CHECK (box.toString () == "Box ((-10, -10), (10, 10))");
                BOOST_CHECK (area (box) == 400);

        }

}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testLineString)
{
        {
                LineString ls;
                ls.add (Point (-10.1, -10.2));
                ls.add (Point (-10.3, 10.4));
                ls.add (Point (10.5, 10.6));
                ls.add (Point (15.7, 0.8));
                // std::cerr << ls.toString () << std::endl;

                BOOST_CHECK (ls.toString () == "LineString ((-10.1, -10.2), (-10.3, 10.4), (10.5, 10.6), (15.7, 0.8))");
        }

}

/**
 *
 */
BOOST_AUTO_TEST_CASE (testBasic)
{
        linestring_2d ls1;
        linestring_2d ls;
        const double c[][2] = { {-50, 50}, {50, 50}, {50, -50}, {-50, -50} };
        append (ls1, c);

        strategy::transform::translate_transformer<point_2d, point_2d> transformer(50, 50);

        typedef strategy::transform::ublas_transformer <point_2d, point_2d, 2, 2> Transformer;

        typedef boost::numeric::ublas::matrix <double> AffineMatrix;

        AffineMatrix m;// = transformer;

//        Transformer t1 = m;
//        transform (ls1, ls, t1);
//        std::cout << boost::geometry::dsv(ls) << std::endl;

/*--------------------------------------------------------------------------*/

        point_2d pkt (5.1, 4.2);
//        std::cout << dsv (pkt) << std::endl;

        BOOST_CHECK (true);
}
 
BOOST_AUTO_TEST_SUITE_END ();
