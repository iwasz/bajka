///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  Date : Nov 26, 2009                                                     *
// *  ~~~~~~                                                                  *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#include "WidgetFactory.h"
//#include "Model.h"
//#include "View.h"
//#include "Controller.h"
//
//namespace M = Model;
//namespace V = View;
//namespace C = Controller;
//
//namespace Util {
//
//Ptr <C::SimpleController> WidgetFactory::createImage (const Core::String &path)
//{
//        Ptr <C::SimpleController> simple (new C::SimpleController);
//        Ptr <M::Image> mImage (new M::Image ());
//        mImage->setPath (path);
//        Ptr <V::Image> vImage (new V::Image ());
//        vImage->setModel (mImage);
////        vImage->init ();
//        simple->setModel (mImage);
//        simple->setWidget (vImage);
//        return simple;
//}
//
//Ptr <C::SimpleController> WidgetFactory::createScreen ()
//{
//        Ptr <C::SimpleController> c (new C::SimpleController);
//        Ptr <View::Screen> v (new View::Screen);
//        Ptr <M::Primitive> m (new M::Primitive);
//
//        v->setModel (m);
//        c->setModel (m);
//        c->setWidget (v);
//
//        return c;
//
//}
//
//Ptr <C::Table> WidgetFactory::createTable (int w, int h)
//{
//        Ptr <C::Table> c (new C::Table (w, h));
//        Ptr <V::EmptyWidget> v (new V::EmptyWidget);
//        Ptr <M::Item> m (new M::Item);
//
//        v->setModel (m);
//        c->setModel (m);
//        c->setWidget (v);
//
//        return c;
//
//}
//
//}
