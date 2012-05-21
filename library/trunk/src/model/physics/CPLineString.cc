/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_CHIPMUNK
#include <chipmunk.h>
#include <cstddef>
#include "CPLineString.h"
#include "Segment.h"
#include "Body.h"
#include "Space.h"

namespace Model {

struct CPLineStringImpl {

        CPLineStringImpl () : point (Geometry::ZERO_POINT), hasPoint (false) {}

        std::vector <cpSegmentShape> shapes;
        Geometry::Point point;
        bool hasPoint;
};

/****************************************************************************/

CPLineString::CPLineString () : radius (1)
{
        impl = new CPLineStringImpl;
}

/****************************************************************************/

CPLineString::~CPLineString()
{
        delete impl;
}

/****************************************************************************/

//void CPLineString::addPoint (Geometry::Point const &p)
//{
//        if (!impl->hasPoint) {
//                impl->point = p;
//                impl->hasPoint = true;
//                return;
//        }
//
//        assertThrow (getParent (), "CPLineString::addPoint : !parent");
//
//        // TODO Kast zalezny od macra RELEASE / DEBUG
//        Body *b = dynamic_cast <Body *> (getParent ());
//        assertThrow (b, "CPLineString::addPoint : dynamic_cast <Body *> (getParent ())")
//
//        cpShape *shape = cpSegmentShapeNew (b->getBody (), cpv (impl->point.x, impl->point.y), cpv (p.x, p.y), radius);
//
//
//        impl->shapes.push_back (reinterpret_cast <cpSegmentShape *> (shape));
//
//        shape = cpSpaceAddShape (Space::getSpace(), shape);
//        cpShapeSetUserData (shape, this);
//
//        // TODO czy to powinna być masa całego body?
//        b->addInertia (cpMomentForSegment (b->getMass (), cpv (impl->point.x, impl->point.y) , cpv (p.x, p.y)));
//
//        impl->point = p;
//
//#if 0
//        std::cerr << p.x << "," << p.y << "," << impl->point.x << "," << impl->point.y << std::endl;
//        std::cerr << offsetof (cpSegmentShape, a) << std::endl;
//        std::cerr << offsetof (cpSegmentShape, n) << std::endl;
//        std::cerr << sizeof (cpSegmentShape) << ", " <<  offsetof (cpSegmentShape, n) - offsetof (cpSegmentShape, a) << ", " << sizeof (cpVect) * 2 <<  std::endl;
//
//        std::cerr << offsetof (cpSegmentShape, n) << std::endl;
//
//        cpSegmentShape sha[2];
//        char *sA = reinterpret_cast <char *> (sha);
//        char *sB = reinterpret_cast <char *> (sha + 1);
//
//        std::cerr <<  "cpShape : " << sB - sA << std::endl;
//
//
//        std::cerr << impl->point.x << "," << impl->point.y << std::endl;
//////        char *c = reinterpret_cast <char *> (shape);
////        char *c = reinterpret_cast <char *> (impl->shapes[0]);
////
////        double *d = reinterpret_cast <double *> (c + offsetof (cpSegmentShape, a));
////        std::cerr << *d << "," << *(d + 1) << std::endl;
////        exit (0);
//#endif
//}

/****************************************************************************/

void CPLineString::setData (Ptr <Geometry::LineString> d)
{
        impl->shapes.resize (d->size () - 1);
//        std::for_each (d->begin (), d->end (), boost::bind (&CPLineString::addPoint, this, _1));

        int j = 0;
        for (Geometry::LineString::const_iterator i = d->begin (); i != d->end (); ++i) {

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
                std::cerr << Geometry::toString (impl->point) << ", " << Geometry::toString (*i) << std::endl;
#endif

                cpShape *shape = cpSpaceAddShape (Space::getSpace(), reinterpret_cast <cpShape *> (segment));
                cpShapeSetUserData (shape, this);

//                // TODO czy to powinna być masa całego body?
//                b->addInertia (cpMomentForSegment (b->getMass (), cpv (impl->point.x, impl->point.y) , cpv (p.x, p.y)));

                impl->point = *i;
       }
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

        ret.numVertices = impl->shapes.size () + 1;

        ret.stride = sizeof (cpSegmentShape);
        ret.pointType = VertexBuffer::DOUBLE;

#if 0
        {
                double *d = reinterpret_cast <double *> (buffer + offsetA);
                std::cerr << *d << "," << *(d + 1) << std::endl;
        }
        {
                double *d = reinterpret_cast <double *> (buffer + offsetA + sizeof (cpSegmentShape));
                std::cerr << *d << "," << *(d + 1) << std::endl;
        }
        {
                double *d = reinterpret_cast <double *> (buffer + offsetA + 2*sizeof (cpSegmentShape));
                std::cerr << *d << "," << *(d + 1) << std::endl;
        }
        {
                double *d = reinterpret_cast <double *> (buffer + offsetA + 3*sizeof (cpSegmentShape));
                std::cerr << *d << "," << *(d + 1) << std::endl;
        }
        {
                double *d = reinterpret_cast <double *> (buffer + offsetA + 4*sizeof (cpSegmentShape));
                std::cerr << *d << "," << *(d + 1) << std::endl;
        }

        exit (0);
#endif

        return ret;
}

} /* namespace Model */
#endif
