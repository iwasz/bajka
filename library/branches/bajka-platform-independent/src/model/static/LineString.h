/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef MODEL_LINESTRING_H_
#define MODEL_LINESTRING_H_

#include "geometry/LineString.h"
#include "model/AbstractModel.h"
#include "model/IVertexBufferEnabled.h"

namespace Model {

class LineString : public AbstractModel, public IVertexBufferEnabled {
public:

        C__ (void)
        b_ ("AbstractModel")

        virtual ~LineString() {}

        Ptr <Geometry::LineString> getData () { return data; }
        m_ (setData) void setData (Ptr <Geometry::LineString> d) { data = d; }

        //--

        Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const;
        bool contains (Geometry::Point const &p) const;
        Geometry::Point computeCenter () const;

        //---

        VertexBuffer getVertexBuffer () const;

private:

        Ptr <Geometry::LineString> data;

        E_ (LineString)

};

} /* namespace Model */
#endif /* LINESTRING_H_ */
