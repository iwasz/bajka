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

        std::vector <cpShape *> shapes;
        Geometry::Point point;
        bool hasPoint;
};

/****************************************************************************/

CPLineString::CPLineString ()
{
        impl = new CPLineStringImpl;
}

/****************************************************************************/

CPLineString::~CPLineString()
{
        delete impl;
}

/****************************************************************************/

void CPLineString::addPoint (Geometry::Point const &p)
{
        if (!impl->hasPoint) {
                impl->point = p;
                impl->hasPoint = true;
                return;
        }

        // TODO Kast zalezny od macra RELEASE / DEBUG
        Body *b = dynamic_cast <Body *> (getParent ());
        cpShape *shape = cpSegmentShapeNew (b->getBody (), cpv (impl->point.x, impl->point.y) , cpv (p.x, p.y), radius);

        impl->shapes.push_back (shape);

        shape = cpSpaceAddShape (Space::getSpace(), shape);
        cpShapeSetUserData (shape, this);

        // TODO czy to powinna być masa całego body?
        b->addInertia (cpMomentForSegment (b->getMass (), cpv (impl->point.x, impl->point.y) , cpv (p.x, p.y)));

        impl->point = p;
}

/****************************************************************************/

void CPLineString::setData (Ptr <Geometry::LineString> d)
{
        std::for_each (d->begin (), d->end (), boost::bind (&CPLineString::addPoint, this, _1));
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

        char *buffer = reinterpret_cast <char *> (impl->shapes[0]);
        ret.buffer = buffer + offsetof (cpSegmentShape, a);
        ret.numVertices = impl->shapes.size () + 1;

        ret.stride = sizeof (cpSegmentShape) - 2 * sizeof (float);

        return ret;
}

/****************************************************************************/

void CPLineString::setParent2 (IModel *p)
{
        AbstractModel::setParent (p);
        IGroup *group = dynamic_cast <IGroup *> (p);
        group->addChild (this);
}


} /* namespace Model */
#endif
