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
        return Geometry::Box::ZERO_BOX;
}

bool LineString::contains (Geometry::Point const &p) const
{
        return false;
}

Geometry::Point LineString::computeCenter () const
{
        return Geometry::ZERO_POINT;
}

VertexBuffer LineString::getVertexBuffer () const
{
        VertexBuffer ret;
        ret.buffer = &data->operator [] (0);
        ret.numVertices = data->size ();
        ret.stride = 0;
        return ret;
}

} /* namespace Model */
