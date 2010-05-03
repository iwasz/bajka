/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 19, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "InclusionService.h"
#include "Point.h"
#include "Rectangle.h"

namespace Util {

bool InclusionService::include (const Model::Rectangle &rect, const Model::Point &point)
{
        return rect.getA ().getX () <= point.getX () &&
                rect.getB ().getX () >= point.getX () &&
                rect.getA ().getY () <= point.getY () &&
                rect.getB ().getY () >= point.getY ();
}

}
