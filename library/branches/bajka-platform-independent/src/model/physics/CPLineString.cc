/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef WITH_CHIPMUNK
#include <chipmunk.h>
#include <cstddef>
#include "CPLineString.h"
#include "geometry/Segment.h"
#include "Body.h"
#include "Space.h"
#include "Platform.h"

namespace Model {

struct CPLineStringImpl {

        CPLineStringImpl () : point (Geometry::ZERO_POINT), hasPoint (false) {}

        std::vector <cpSegmentShape> shapes;
        Geometry::Point point;
        bool hasPoint;
        Ptr <Geometry::LineString> data;
};

/****************************************************************************/

CPLineString::CPLineString () : radius (1),
        sensor (false),
        elasticity (0),
        friction (1),
        collisionType (0),
        group (CP_NO_GROUP),
        layers (CP_ALL_LAYERS)
{
        impl = new CPLineStringImpl;
}

/****************************************************************************/

CPLineString::~CPLineString()
{
        delete impl;
}

/****************************************************************************/

void CPLineString::init ()
{
        impl->shapes.resize (impl->data->size () - 1);

        int j = 0;
        for (Geometry::LineString::const_iterator i = impl->data->begin (); i != impl->data->end (); ++i) {

                if (!impl->hasPoint) {
                        impl->point = *i;
                        impl->hasPoint = true;
                        continue;
                }

                assertThrow (getParent (), "CPLineString::addPoint : !parent");
                // TODO Kast zalezny od macra RELEASE / DEBUG
                Body *b = dynamic_cast <Body *> (getParent ());
                assertThrow (b, "CPLineString::addPoint : dynamic_cast <Body *> (getParent ())")

                cpSegmentShape *segment = &impl->shapes[j++];
                cpSegmentShapeInit (segment, b->getBody (), cpv (impl->point.x, impl->point.y), cpv (i->x, i->y), radius);

#if 0
                LOGI ("%s, %s", Geometry::toString (impl->point).c_str (), Geometry::toString (*i).c_str ());
#endif

                cpShape *shape = cpSpaceAddShape (Space::getSpace(), reinterpret_cast <cpShape *> (segment));
                cpShapeSetUserData (shape, this);
                cpShapeSetSensor (shape, sensor);
                cpShapeSetElasticity (shape, elasticity);
                cpShapeSetFriction (shape, friction);
                cpShapeSetCollisionType (shape, collisionType);
                cpShapeSetGroup (shape, group);
                cpShapeSetLayers (shape, layers);

//                // TODO czy to powinna być masa całego body?
//                b->addInertia (cpMomentForSegment (b->getMass (), cpv (impl->point.x, impl->point.y) , cpv (p.x, p.y)));

                impl->point = *i;
       }
}

/****************************************************************************/

void CPLineString::setData (Ptr <Geometry::LineString> d)
{
        impl->data = d;
}

/****************************************************************************/

Geometry::Box CPLineString::getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const
{
        return Geometry::Box::ZERO_BOX;
}

/****************************************************************************/

bool CPLineString::contains (Geometry::Point const &p) const
{
        return false;
}

/****************************************************************************/

Geometry::Point CPLineString::computeCenter () const
{
        return Geometry::ZERO_POINT;
}

/****************************************************************************/

VertexBuffer CPLineString::getVertexBuffer () const
{
        VertexBuffer ret;

        size_t offsetA = offsetof (cpSegmentShape, a);

        char *buffer = reinterpret_cast <char *> (&impl->shapes[0]);
        ret.buffer = buffer + offsetA;

        ret.numVertices = impl->shapes.size ();

        ret.stride = sizeof (cpSegmentShape);

//#ifdef ANDROID
//        ret.pointType = VertexBuffer::FLOAT;
//#else
//        ret.pointType = VertexBuffer::DOUBLE;
//#endif

#if 0
        {
                double *d = reinterpret_cast <double *> (buffer + offsetA);
                LOGI ("%f, %f", *d, *(d + 1));
        }
        {
                double *d = reinterpret_cast <double *> (buffer + offsetA + sizeof (cpSegmentShape));
                LOGI ("%f, %f", *d, *(d + 1));
        }
        {
                double *d = reinterpret_cast <double *> (buffer + offsetA + 2*sizeof (cpSegmentShape));
                LOGI ("%f, %f", *d, *(d + 1));
        }
        {
                double *d = reinterpret_cast <double *> (buffer + offsetA + 3*sizeof (cpSegmentShape));
                LOGI ("%f, %f", *d, *(d + 1));
        }
        {
                double *d = reinterpret_cast <double *> (buffer + offsetA + 4*sizeof (cpSegmentShape));
                LOGI ("%f, %f", *d, *(d + 1));
        }

        exit (0);
#endif

        buffer = reinterpret_cast <char *> (&impl->shapes.back ());
        ret.extraSegment = buffer + offsetA;

        return ret;
}

/****************************************************************************/

cpBody *CPLineString::getCPBody ()
{
        return dynamic_cast <Body *> (getParent ())->getBody ();
}

/****************************************************************************/

Body *CPLineString::getBody ()
{
        return dynamic_cast <Body *> (getParent ());
}

/****************************************************************************/

Geometry::Point CPLineString::getSurfaceVelocity () const
{
        assert (0);
        return Geometry::ZERO_POINT;
}

/****************************************************************************/

void CPLineString::setSurfaceVelocity (Geometry::Point const &)
{
        assert (0);
}

} /* namespace Model */
#endif
