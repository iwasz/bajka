/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "InclusionService.h"
#include "geometry/Point.h"
#include "geometry/Box.h"

namespace Util {

bool InclusionService::include (const Geometry::Box &rect, const Geometry::Point &point)
{
        return rect.getX1 () <= point.getX () &&
                rect.getX2 () >= point.getX () &&
                rect.getY1 () <= point.getY () &&
                rect.getY2 () >= point.getY ();
}

}
