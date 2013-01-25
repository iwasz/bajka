/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Ring.h"

namespace Model {

Geometry::Box Ring::getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const
{
        // TODO
        return Geometry::Box::ZERO_BOX;
}

/****************************************************************************/

bool Ring::contains (Geometry::Point const &p) const
{
        // TODO - ale ring nie ma powierzchni, więc czy może coś zawierać? No może w środku...
        return false;
}

/****************************************************************************/

Geometry::Point Ring::computeCenter () const
{
        return Geometry::ZERO_POINT;
}

/****************************************************************************/

VertexBuffer Ring::getVertexBuffer () const
{
        VertexBuffer ret;
        ret.buffer = &data->operator [] (0);
        ret.numVertices = data->size ();
        ret.stride = 0;
        return ret;
}

} /* namespace Model */
