/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ScrollMarginController.h"
#include "geometry/Utils.h"
#include "../../model/Box.h"

namespace Service {
using namespace Core;
using namespace Signal;
namespace G = Geometry;

void ScrollMarginController::setModel (Ptr <Model::IModel> m)
{
        SimpleController::setModel (m);
        box = dynamic_cast <Model::Box *> (m.get ());
        ASSERT (box, "Failed to cast to Model::Box *");
}

bool ScrollMarginController::onMouseMotion (Event::MouseMotionEvent *e)
{
        if (!e || !box) {
                return true;
        }

        VariantVector args;
        G::Point p = getModel ()->screenToModel (e->getPosition ());

        if (type == TOP) {
                double h = box->getHeight ();
                double speed = p.getY () / h;

                // TODO to nie może być przez taką listę. To bez sensu jest.
                args.add (vcast <Variant> (speed));
                sender.emit ("/scroll/up", args);
        }

        if (type == BOTTOM) {
                double h = box->getHeight ();
                double speed = ((h - p.getY ()) / h);

                args.add (variant_cast <Variant> (speed));
                sender.emit ("/scroll/down", args);
        }

        if (type == LEFT) {
                double w = box->getWidth ();
                double speed = ((w - p.getX ()) / w);

                args.add (variant_cast <Variant> (speed));
                sender.emit ("/scroll/left", args);
        }

        if (type == RIGHT) {
                double w = box->getWidth ();
                double speed = (p.getX () / w);

                args.add (variant_cast <Variant> (speed));
                sender.emit ("/scroll/right", args);
        }
}

/****************************************************************************/

bool ScrollMarginController::onMouseOut (Event::MouseMotionEvent *e)
{
        VariantVector args;
        args.add (variant_cast <Variant> (0.0));

        if (type == TOP) {
                sender.emit ("/scroll/up", args);
        }

        if (type == BOTTOM) {
                sender.emit ("/scroll/down", args);
        }

        if (type == LEFT) {
                sender.emit ("/scroll/left", args);
        }

        if (type == RIGHT) {
                sender.emit ("/scroll/right", args);
        }
}

}
