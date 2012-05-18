/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef USE_CHIPMUNK
#include <chipmunk.h>
#include "CPLineString.h"
#include "Segment.h"
#include "Body.h"
#include "Space.h"

namespace Model {

struct CPLineStringImpl {

        CPLineStringImpl () : hasPoint (false) {}

        std::vector <cpShape *> shapes;
        Geometry::Point startPoint;
        bool hasPoint;
};

CPLineString::CPLineString ()
{
        impl = new CPLineStringImpl;
}

CPLineString::~CPLineString()
{
        delete impl;
}

void CPLineString::addPoint (Geometry::Point const &p)
{
        if (!impl->hasPoint) {
                impl->startPoint = p;
                impl->hasPoint = true;
                return;
        }

        // TODO Kast zalezny od macra RELEASE / DEBUG
        Body *b = dynamic_cast <Body *> (getParent ());
        cpShape *shape = cpSegmentShapeNew (b->getBody (), cpv (impl->startPoint.x, impl->startPoint.y) , cpv (p.x, p.y), radius);

        impl->shapes.push_back (shape);

        shape = cpSpaceAddShape (Space::getSpace(), shape);
        cpShapeSetUserData (shape, this);

        // TODO czy to powinna być masa całego body?
        b->addInertia (cpMomentForSegment (b->getMass (), cpv (impl->startPoint.x, impl->startPoint.y) , cpv (p.x, p.y)));

        impl->startPoint = p;
}

void CPLineString::setData (Ptr <Geometry::LineString> d)
{
        std::for_each (d->begin (), d->end (), boost::bind (&CPLineString::addPoint, this, _1));
}

Geometry::Box CPLineString::getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const
{

}

bool CPLineString::contains (Geometry::Point const &p) const
{

}

Geometry::Point CPLineString::computeCenter () const
{

}

void *CPLineString::getPointArray () const
{
}

size_t CPLineString::getNumberOfPoints () const
{
}

} /* namespace Model */
#endif
