/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "LineString.h"

namespace Model {

Geometry::Box LineString::getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const
{

}

bool LineString::contains (Geometry::Point const &p) const
{

}

Geometry::Point LineString::computeCenter () const
{

}

void *LineString::getPointArray () const
{
        return &data->operator [] (0);
}

size_t LineString::getNumberOfPoints () const
{
        return data->size ();
}

} /* namespace Model */
