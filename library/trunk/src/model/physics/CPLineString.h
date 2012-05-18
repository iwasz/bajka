/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_CHIPMUNK
#ifndef PHYSICS_MODEL_LINESTRING_H_
#define PHYSICS_MODEL_LINESTRING_H_

#include "../../geometry/LineString.h"
#include "../AbstractModel.h"
#include "../IPointArray.h"

namespace Model {
class CPLineStringImpl;

class CPLineString : public AbstractModel, public IPointArray {
public:

        C__ (void)
        b_ ("AbstractModel")

        CPLineString ();
        virtual ~CPLineString();

        m_ (setData) void setData (Ptr <Geometry::LineString> d);
        void addPoint (Geometry::Point const &p);

        float getRadius () const { return radius; }
        m_ (setRadius) void setRadius (float f) { radius = f; }

        //--

        Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const;
        bool contains (Geometry::Point const &p) const;
        Geometry::Point computeCenter () const;

        //---

        void *getPointArray () const;
        size_t getNumberOfPoints () const;

private:

        CPLineStringImpl *impl;
        float radius;

        E_ (CPLineString)

};

} /* namespace Model */
#endif /* LINESTRING_H_ */
#endif
