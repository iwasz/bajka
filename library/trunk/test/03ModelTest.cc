#if 0
//#include <boost/test/unit_test.hpp>
//#include <boost/geometry/geometry.hpp>
//#include <sstream>
//#include <Pointer.h>
//
//#include "IModel.h"
//#include "../model/Box.h"
//
//// Procentowy dopuszcalny błąd w porównaniach doubli.
//#define CLOSE 0.0000001
//
//using namespace boost;
//using namespace boost::geometry;
//
//using namespace Geometry;
//
//namespace M = Model;
//namespace C = Controller;
//
///****************************************************************************/
//
////void CHECK_POINT (Geometry::Point const &p, double x, double y)
//#define CHECK_POINT(p,x,y)                                                \
//{                                                                         \
//        if ((x) != 0.0) {                                                 \
//                BOOST_CHECK_CLOSE ((p).getX (), (x), CLOSE);              \
//        }                                                                 \
//        else {                                                            \
//                BOOST_CHECK_CLOSE ((p).getX () + 1, (x) + 1, CLOSE);      \
//        }                                                                 \
//                                                                          \
//        if ((y) != 0.0) {                                                 \
//                BOOST_CHECK_CLOSE ((p).getY (), (y), CLOSE);              \
//        }                                                                 \
//        else {                                                            \
//                BOOST_CHECK_CLOSE ((p).getY () + 1, (y) + 1, CLOSE);      \
//        }                                                                 \
//}
//
///****************************************************************************/
//
//BOOST_AUTO_TEST_SUITE (ModelTest);
//
///**
// *
// */
//BOOST_AUTO_TEST_CASE (testPoint)
//{
//        {
//                Point p (1.2, 3.4);
//                BOOST_CHECK (p.toString () == "Point (1.2, 3.4)");
//        }
//
///*--------------------------------------------------------------------------*/
//
//        {
//                Point p01 (1.2, 3.4);
//                Point p02 (3.4, 1.2);
//                p02 += p01;
//                BOOST_CHECK (p02 == Point (4.6, 4.6));
//        }
//
///*--------------------------------------------------------------------------*/
//
//        {
//                Point p01 (1.2, 3.4);
//                Point p02 (3.4, 1.2);
//                Point p = p02 + p01;
//                BOOST_CHECK (p == Point (4.6, 4.6));
//        }
//}
//
///**
// *
// */
//BOOST_AUTO_TEST_CASE (testBox)
//{
//        {
//                Box box (-10, -10, 10, 10);
//                BOOST_CHECK (box.toString () == "Box ((-10, -10), (10, 10))");
//                BOOST_CHECK (area (box) == 400);
//        }
//
//}
//
///**
// *
// */
//BOOST_AUTO_TEST_CASE (testLineString)
//{
//        {
//                LineString ls;
//                ls.add (Point (-10.1, -10.2));
//                ls.add (Point (-10.3, 10.4));
//                ls.add (Point (10.5, 10.6));
//                ls.add (Point (15.7, 0.8));
//                // std::cerr << ls.toString () << std::endl;
//
//                BOOST_CHECK (ls.toString () == "LineString ((-10.1, -10.2), (-10.3, 10.4), (10.5, 10.6), (15.7, 0.8))");
//        }
//
//}
//
///**
// *
// */
//BOOST_AUTO_TEST_CASE (testBasic)
//{
//        linestring_2d ls1;
//        linestring_2d ls;
//        const double c[][2] = { {-50, 50}, {50, 50}, {50, -50}, {-50, -50} };
//        append (ls1, c);
//
//        strategy::transform::translate_transformer<point_2d, point_2d> transformer(50, 50);
//
//        typedef strategy::transform::ublas_transformer <point_2d, point_2d, 2, 2> Transformer;
//
//        typedef boost::numeric::ublas::matrix <double> AffineMatrix;
//
//        AffineMatrix m;// = transformer;
//
////        Transformer t1 = m;
////        transform (ls1, ls, t1);
////        std::cout << boost::geometry::dsv(ls) << std::endl;
//
///*--------------------------------------------------------------------------*/
//
//        point_2d pkt (5.1, 4.2);
////        std::cout << dsv (pkt) << std::endl;
//
//        BOOST_CHECK (true);
//}
//
//BOOST_AUTO_TEST_CASE (testAffine)
//{
//        Ptr <C::IController> c0 = Ptr <C::IController> (new C::SimpleController);
////        Ptr <Model::IModel> b0 = Ptr <Model::IModel> (new Model::Box (-50, -50, 50, 50));
//        Ptr <Model::IModel> b0 = Ptr <Model::IModel> (new Model::Box (-50, -50, 50, 50));
//        c0->setModel (b0);
//
//        Ptr <C::IController> c1 = Ptr <C::IController> (new C::SimpleController);
//        Ptr <Model::IModel> b1 = Ptr <Model::IModel> (new Model::Box (-40, -40, 40, 40));
//        c1->setModel (b1);
//
//        Ptr <C::IController> c2 = Ptr <C::IController> (new C::SimpleController);
//        Ptr <Model::IModel> b2 = Ptr <Model::IModel> (new Model::Box (-30, -30, 30, 30));
//        c2->setModel (b2);
//
//        c0->addChild (c1);
//        c1->addChild (c2);
//
////TODO to nie przechodzi poprawic
////        BOOST_CHECK (Point (0, 0) == b0->modelToScreen (Point (0, 0)));
//
//}
//
///**
// * Testuje parę metod IModel::setMove, IModel::
// */
//BOOST_AUTO_TEST_CASE (testMoveMethod)
//{
//        Ptr <M::Box> b = M::Box::create (10, 10, 20, 20);
//        b->setMove (Point (5, 5));
//        BOOST_CHECK_EQUAL (b->getMove (), Point (5, 5));
//}
//
///**
// * Testuje pozycjonowanie absolutne.
// */
//BOOST_AUTO_TEST_CASE (testPositionMethod)
//{
//        Ptr <M::Box> b = M::Box::create (0, 0, 10, 10);
//        b->setPosition (Point (5, 5));
//        BOOST_CHECK_EQUAL (b->getMove (), Point (5, 5));
//
//        b->setPosition (Point (5, 5));
//        BOOST_CHECK_EQUAL (b->getMove (), Point (5, 5));
//
//        b->setPosition (Point (10, 10));
//        BOOST_CHECK_EQUAL (b->getMove (), Point (10, 10));
//
//        b->setPosition (Point (-10, 5));
//        BOOST_CHECK_EQUAL (b->getMove (), Point (-10, 5));
//
//        b->setRotate (30);
//        BOOST_CHECK_EQUAL (b->getMove (), Point (-10, 5));
//
//        b->setResize (1.5, 1.5);
//        BOOST_CHECK_EQUAL (b->getMove (), Point (-10, 5));
//}
//
///**
// * Testuje setRotate i getRotate (bez punktu).
// */
//BOOST_AUTO_TEST_CASE (testRotateMethod)
//{
//        {
//                Ptr <M::Box> b = M::Box::create (10, 10, 20, 20);
//                b->setRotate (45);
//                BOOST_CHECK_CLOSE (b->getRotate (), 45, CLOSE);
//        }
//
//        {
//                Ptr <M::Box> b = M::Box::create (10, 10, 20, 20);
//                b->setRotateRad (M_PI / 4);
//                BOOST_CHECK_CLOSE (b->getRotateRad (), M_PI / 4, CLOSE);
//        }
//
//        {
//                Ptr <M::Box> b = M::Box::create (10, 10, 20, 20);
//                b->setRotateRad (M_PI / 4);
//                BOOST_CHECK_CLOSE (b->getRotate (), 45, CLOSE);
//        }
//
//        {
//                Ptr <M::Box> b = M::Box::create (10, 10, 20, 20);
//                b->setMove (Point (5, 5));
//                b->setRotate (45);
//                BOOST_CHECK_CLOSE (b->getRotate (), 45, CLOSE);
//        }
//}
//
///**
// * Testuje setRotate i getRotate (z punktem).
// */
//BOOST_AUTO_TEST_CASE (testRotateOriginMethod)
//{
//        {
//                Ptr <M::Box> b = M::Box::create (10, 10, 20, 20);
//                b->setRotate (45, Point (20, 20));
//                BOOST_CHECK_CLOSE (b->getRotate (), 45, CLOSE);
//        }
//
//        {
//                Ptr <M::Box> b = M::Box::create (10, 10, 20, 20);
//                b->setRotateRad (M_PI / 4, Point (10, 10));
//                BOOST_CHECK_CLOSE (b->getRotateRad (), M_PI / 4, CLOSE);
//        }
//
//        {
//                Ptr <M::Box> b = M::Box::create (10, 10, 20, 20);
//                b->setRotateRad (M_PI / 4, Point (50, 70));
//                BOOST_CHECK_CLOSE (b->getRotate (), 45, CLOSE);
//        }
//
//        {
//                Ptr <M::Box> b = M::Box::create (10, 10, 20, 20);
//                b->setMove (Point (5, 5));
//                b->setRotate (45, Point (15, 25));
//                BOOST_CHECK_CLOSE (b->getRotate (), 45, CLOSE);
//        }
//}
//
///**
// * A teraz sprawdzam współrzędne które powstawły w wyniku rotacji. Na przykład pierwsza
// * rotacja jest względem punktu 20, 20.
// */
//BOOST_AUTO_TEST_CASE (testRotate2)
//{
//        {
//                Ptr <M::Box> b = M::Box::create (0, 0, 10, 10);
//                b->setRotate (90);
//
//                Point p1 = b->modelToScreen (b->getLL ());
//                Point p2 = b->modelToScreen (b->getUR ());
//
//                BOOST_CHECK_EQUAL (p2, Point (-10, 10));
//                BOOST_CHECK_EQUAL (p1, Point (0, 0));
//                BOOST_CHECK_EQUAL (b->getMove (), Point (0, 0));
//
//                b->setRotate (45);
//
//                p1 = b->modelToScreen (b->getLL ());
//                p2 = b->modelToScreen (b->getUR ());
//
//                BOOST_CHECK_EQUAL (b->getMove (), Point (0, 0));
//                BOOST_CHECK_CLOSE (p2.getX (), -10.0 * M_SQRT2, CLOSE);
//                BOOST_CHECK_CLOSE (p2.getY () + 1, 1, CLOSE);
//                BOOST_CHECK_CLOSE (p1.getX (), 0, CLOSE);
//                BOOST_CHECK_CLOSE (p1.getY (), 0, CLOSE);
//        }
//
//        {
//                Ptr <M::Box> b = M::Box::create (0, 0, 10, 10);
//                b->setRotate (90, Point (5, 5));
//
//                Point ll = b->modelToScreen (b->getLL ());
//                Point ur = b->modelToScreen (b->getUR ());
//
//                CHECK_POINT (ur, 0, 10);
//                CHECK_POINT (ll, 10, 0);
//        }
//
//        {
//                Ptr <M::Box> b = M::Box::create (0, 0, 10, 10);
//                b->setRotate (45, Point (5, 5));
//
//                Point ll = b->modelToScreen (b->getLL ());
//                Point ur = b->modelToScreen (b->getUR ());
//
//                CHECK_POINT (ur, 5, 5 + 5*M_SQRT2);
//                CHECK_POINT (ll, 5, 5 - 5*M_SQRT2);
//        }
//
//        {
//                Ptr <M::Box> b = M::Box::create (0, 0, 10, 10);
//                b->setMove (Point (5, 5));
//                b->setRotate (90, Point (5, 5));
//
//                Point ll = b->modelToScreen (b->getLL ());
//                Point ur = b->modelToScreen (b->getUR ());
//
//                CHECK_POINT (ur, 5, 15);
//                CHECK_POINT (ll, 15, 5);
//        }
//}
//
///**
// * Skalowaine
// */
//BOOST_AUTO_TEST_CASE (testResizeMethod)
//{
//        {
//                Ptr <M::Box> b = M::Box::create (0, 0, 10, 10);
//                b->setResizeW (2);
//                b->setResizeH (2);
//                BOOST_CHECK_CLOSE (b->getResizeW (), 2, CLOSE);
//                BOOST_CHECK_CLOSE (b->getResizeH (), 2, CLOSE);
//
//                Point ll = b->modelToScreen (b->getLL ());
//                Point ur = b->modelToScreen (b->getUR ());
//
//                CHECK_POINT (ur, 20, 20);
//                CHECK_POINT (ll, 0, 0);
//        }
//
//        {
//                Ptr <M::Box> b = M::Box::create (0, 0, 10, 10);
//                b->setMove (Point (5, 5));
//                b->setResizeW (2);
//                b->setResizeH (2);
//                BOOST_CHECK_CLOSE (b->getResizeW (), 2, CLOSE);
//                BOOST_CHECK_CLOSE (b->getResizeH (), 2, CLOSE);
//
//                Point ll = b->modelToScreen (b->getLL ());
//                Point ur = b->modelToScreen (b->getUR ());
//
//                CHECK_POINT (ur, 25, 25);
//                CHECK_POINT (ll, 5, 5);
//        }
//}
//
//BOOST_AUTO_TEST_SUITE_END ();
#endif
