/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "ScrollMarginController.h"
#include "geometry/Utils.h"

namespace Service {
using namespace Core;
using namespace Signal;

bool ScrollMarginController::onMouseMotion (Event::MouseMotionEvent *e)
{
        if (!e || !getModel ()) {
                return true;
        }

        VariantVector args;

        // TODO ale, ale! Pozycja kursora powinna być tutaj względem widgetu!
        // Co mnie obchodzą world coordinates?
        e->getPosition ();

        std::cerr << e->getPosition () << std::endl;


        // bottom margin
        if (type == "bottom") {
                args.add (variant_cast <Variant> (1));
                // TODO To trzeba zbindować dynamicznie w kontenerze, a nie ściezka na sztywno.
                sender.emit ("/a/down", args);

        }

}

}
