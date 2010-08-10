/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ScrollMarginController.h"
#include "geometry/Utils.h"
#include "IModel.h"

namespace Service {
using namespace Core;
using namespace Signal;
namespace G = Geometry;

bool ScrollMarginController::onMouseMotion (Event::MouseMotionEvent *e)
{
        if (!e || !getModel ()) {
                return true;
        }


        G::Point p = getModel ()->screenToModel (e->getPosition ());

        if (type == TOP) {
                VariantVector args;
                double h = getModel ()->getHeight ();
                double speed = p.getY () / h;
                std::cerr << speed << std::endl;

                // TODO to nie może być przez taką listę. To bez sensu jest.
                Variant v /*= variant_cast <Variant> (speed)*/;
                args.add (v);
                sender.emit ("/a/up", args);
        }

//        if (type == BOTTOM) {
//                double h = getModel ()->getHeight ();
//                double speed = ((h - p.getY ()) / h);
//                std::cerr << speed << std::endl;
//
//                args.add (variant_cast <Variant> (speed));
//                sender.emit ("/a/down");
//        }
//
//        if (type == LEFT) {
//                double w = getModel ()->getWidth ();
//                double speed = ((w - p.getX ()) / w);
//                std::cerr << speed << std::endl;
//
//                args.add (variant_cast <Variant> (speed));
//                sender.emit ("/a/left");
//        }
//
//        if (type == RIGHT) {
//                double w = getModel ()->getWidth ();
//                double speed = (p.getX () / w);
//                std::cerr << speed << std::endl;
//
//                args.add (variant_cast <Variant> (speed));
//                sender.emit ("/a/right");
//        }
}

}
