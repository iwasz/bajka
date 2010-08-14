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


        VariantVector args;
        G::Point p = getModel ()->screenToModel (e->getPosition ());

        if (type == TOP) {
                double h = getModel ()->getHeight ();
                double speed = p.getY () / h;

                // TODO to nie może być przez taką listę. To bez sensu jest.
                args.add (vcast <Variant> (speed));
                sender.emit ("/scroll/up", args);
        }

        if (type == BOTTOM) {
                double h = getModel ()->getHeight ();
                double speed = ((h - p.getY ()) / h);

                args.add (variant_cast <Variant> (speed));
                sender.emit ("/scroll/down", args);
        }

        if (type == LEFT) {
                double w = getModel ()->getWidth ();
                double speed = ((w - p.getX ()) / w);

                args.add (variant_cast <Variant> (speed));
                sender.emit ("/scroll/left", args);
        }

        if (type == RIGHT) {
                double w = getModel ()->getWidth ();
                double speed = (p.getX () / w);

                args.add (variant_cast <Variant> (speed));
                sender.emit ("/scroll/right", args);
        }
}

/****************************************************************************/

bool ScrollMarginController::onMouseOut (Event::MouseMotionEvent *e)
{
        sender.emit ("/scroll/stop");
}

}
