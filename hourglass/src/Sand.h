/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef HOURGLASS_SAND_H_
#define HOURGLASS_SAND_H_

#include <AbstractModel.h>
#include <IVertexBufferEnabled.h>

class SandImpl;

/**
 *
 */
class Sand : public AbstractModel, public IVertexBufferEnabled {
public:

        C__ (void)
        b_ ("AbstractModel")

        Sand ();
        virtual ~Sand();

        m_ (setData) void setData (Ptr <Geometry::LineString> d);

        float getRadius () const { return radius; }
        m_ (setRadius) void setRadius (float f) { radius = f; }

/*--------------------------------------------------------------------------*/

        Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const;
        bool contains (Geometry::Point const &p) const;
        Geometry::Point computeCenter () const;

/*--------------------------------------------------------------------------*/

        VertexBuffer getVertexBuffer () const;

private:

        CPLineStringImpl *impl;

        E_ (Sand)

};

#endif
