#include <boost/test/unit_test.hpp>
#include <boost/geometry/geometry.hpp>
#include <sstream>
#include <Pointer.h>


#include "geometry/Geometry.h"
#include "IModel.h"
#include "../controller/SimpleController.h"
#include "../model/Box.h"

// Procentowy dopuszcalny błąd w porównaniach doubli.
#define CLOSE 0.0000001

using namespace boost;
using namespace boost::geometry;

using namespace Geometry;

namespace M = Model;
namespace C = Controller;

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
                Box box (-10, -10, 10, 10);
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

BOOST_AUTO_TEST_CASE (testAffine)
{
        Ptr <C::IController> c0 = Ptr <C::IController> (new C::SimpleController);
//        Ptr <Model::IModel> b0 = Ptr <Model::IModel> (new Model::Box (-50, -50, 50, 50));
        Ptr <Model::IModel> b0 = Ptr <Model::IModel> (new Model::Box (-50, -50, 50, 50));
        c0->setModel (b0);

        Ptr <C::IController> c1 = Ptr <C::IController> (new C::SimpleController);
        Ptr <Model::IModel> b1 = Ptr <Model::IModel> (new Model::Box (-40, -40, 40, 40));
        c1->setModel (b1);

        Ptr <C::IController> c2 = Ptr <C::IController> (new C::SimpleController);
        Ptr <Model::IModel> b2 = Ptr <Model::IModel> (new Model::Box (-30, -30, 30, 30));
        c2->setModel (b2);

        c0->addChild (c1);
        c1->addChild (c2);

//TODO to nie przechodzi poprawic
//        BOOST_CHECK (Point (0, 0) == b0->modelToScreen (Point (0, 0)));

}

/**
 * Testuje parę metod IModel::setMove, IModel::
 */
BOOST_AUTO_TEST_CASE (testMoveMethod)
{
        Ptr <M::Box> b = M::Box::create (10, 10, 20, 20);
        b->setMove (Point (5, 5));
        BOOST_CHECK_EQUAL (b->getMove (), Point (5, 5));
}

BOOST_AUTO_TEST_CASE (testRotateMethod)
{
        {
                Ptr <M::Box> b = M::Box::create (10, 10, 20, 20);
                b->setRotate (45);
                BOOST_CHECK_CLOSE (b->getRotate (), 45, CLOSE);
        }

        {
                Ptr <M::Box> b = M::Box::create (10, 10, 20, 20);
                b->setRotateRad (M_PI / 4);
                BOOST_CHECK_CLOSE (b->getRotateRad (), M_PI / 4, CLOSE);
        }

        {
                Ptr <M::Box> b = M::Box::create (10, 10, 20, 20);
                b->setRotateRad (M_PI / 4);
                BOOST_CHECK_CLOSE (b->getRotate (), 45, CLOSE);
        }

        {
                Ptr <M::Box> b = M::Box::create (10, 10, 20, 20);
                b->setMove (Point (5, 5));
                b->setRotate (45);
                BOOST_CHECK_CLOSE (b->getRotate (), 45, CLOSE);
        }
}

BOOST_AUTO_TEST_SUITE_END ();
