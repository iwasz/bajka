/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MODEL_RING_BAJKA_H_
#define MODEL_RING_BAJKA_H_

#include "geometry/Ring.h"
#include "model/AbstractModel.h"
#include "model/IVertexBufferEnabled.h"

namespace Model {

/**
 *  A linestring (named so by OGC) is a collection (default a vector) of points.
 */
class Ring : public AbstractModel, public IVertexBufferEnabled {
public:

        C__ (void)
        b_ ("AbstractModel")

        Ring () : data (NULL) {}
        virtual ~Ring() {}

        Geometry::Ring *getData () { return data; }
        Geometry::Ring const *getData () const { return data; }
        m_ (setData) void setData (Geometry::Ring *d) { data = d; }

        //--

        Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const;
        bool contains (Geometry::Point const &p) const;
        Geometry::Point computeCenter () const;

        //---

        VertexBuffer getVertexBuffer () const;

private:

        Geometry::Ring *data;

        E_ (Ring)

};

} /* namespace Model */
#endif /* LINESTRING_H_ */
