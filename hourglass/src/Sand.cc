/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <chipmunk.h>
#include <cstddef>
#include <physics/Space.h>
#include "Sand.h"
#include <android/android_native_app_glue.h>

#include <Points.h>
#include <Primitive.h>
#include <physics/StaticBody.h>
#include <physics/CPLineString.h>

using namespace Model;

struct SandImpl {

        std::vector <cpCircleShape> shapes;
        std::vector <cpBody> bodies;

};

/****************************************************************************/

void Sand::addGrain (int i, int j, float densityX, float densityY, int cnt) {

        cpBody* body = &impl->bodies[cnt];
//        cpFloat inertia = cpMomentForCircle (mass, 0, radius, cpvzero);
        cpFloat inertia = 0.1;
        cpSpaceAddBody (Space::getSpace(), cpBodyInit (body, mass, inertia));
        cpBodySetPos (body, cpv (ll.x + i * densityX, ll.y + j * densityY));

        cpCircleShape *circleShape = &impl->shapes[cnt];
        cpCircleShapeInit (circleShape, body, radius, cpvzero);
        cpShape* shape = cpSpaceAddShape (Space::getSpace(), reinterpret_cast <cpShape *> (circleShape));
        cpShapeSetElasticity (shape, elasticity);
        cpShapeSetFriction (shape, friction);
}

/****************************************************************************/

void Sand::init ()
{
        app_dummy();

        impl->shapes.resize (grainNo);
        impl->bodies.resize (grainNo);

        int a = int (sqrt (width * grainNo / height) + 0.5);
        int b = grainNo / a;
        int mod = grainNo % a;

        float densityX = width / a;
        float densityY = height / b;

        int cnt = 0, i = 0, j = 0;

        for (j = 0; j < b; ++j) {
                for (i = 0; i < a; ++i) {
                        addGrain (i, j, densityX, densityY, cnt);
                        ++cnt;
                }
        }

        for (i = 0; i < mod; ++i) {
                addGrain (i, j, densityX, densityY, cnt);
                ++cnt;
        }
}

/****************************************************************************/

Sand::Sand () :
                width (0),
                height (0),
                grainNo (0),
                radius (0),
                mass (0),
                elasticity (0),
                friction (0)
{
        impl = new SandImpl;
}

/****************************************************************************/

Sand::~Sand()
{
        delete impl;
}

/****************************************************************************/

Geometry::Box Sand::getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const
{
        return Geometry::Box::ZERO_BOX;
}

/****************************************************************************/

bool Sand::contains (Geometry::Point const &p) const
{
        return false;
}

/****************************************************************************/

Geometry::Point Sand::computeCenter () const
{
        return Geometry::ZERO_POINT;
}

/****************************************************************************/


VertexBuffer Sand::getVertexBuffer () const
{
        VertexBuffer ret;

        size_t offset = offsetof (cpBody, p);
        char *buffer = reinterpret_cast <char *> (&impl->bodies.front ());

        ret.buffer = buffer + offset;
        ret.numVertices = grainNo;
        ret.stride = sizeof (cpBody);

#ifdef ANDROID
        ret.pointType = VertexBuffer::FLOAT;
#else
        ret.pointType = VertexBuffer::DOUBLE;
#endif


#if 0
        {
                double *d = reinterpret_cast <double *> (buffer + offset);
                std::cerr << *d << "," << *(d + 1) << std::endl;
        }
#endif

        return ret;
}
