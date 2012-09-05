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
#include "IVertexBufferEnabled.h"
#include "ICPShape.h"

namespace Model {
class CPLineStringImpl;

/**
 *
 */
class CPLineString : public AbstractModel, public IVertexBufferEnabled, public ICPShape {
public:

        C__ (void)
        b_ ("AbstractModel", "ICPShape")

        CPLineString ();
        virtual ~CPLineString();

        m_ (init) void init ();
        m_ (setData) void setData (Ptr <Geometry::LineString> d);

        float getRadius () const { return radius; }
        m_ (setRadius) void setRadius (float f) { radius = f; }

/*--------------------------------------------------------------------------*/

        virtual cpBody *getCPBody ();
        virtual Body *getBody ();

        virtual bool getSensor () const { return sensor; }
        virtual void setSensor (bool b) { sensor = b; }

        virtual double getElasticity () const { return elasticity; }
        virtual void setElasticity (double e) { elasticity = e; }

        virtual double getFriction () const { return friction; }
        virtual void setFriction (double f) { friction = f; }

        virtual Geometry::Point getSurfaceVelocity () const;
        virtual void setSurfaceVelocity (Geometry::Point const &);

        virtual cpCollisionType getCollisionType () const { return collisionType; }
        virtual void setCollisionType (cpCollisionType ct) { collisionType  = ct; }

        virtual cpGroup getGroup () const { return group; }
        virtual void setGroup (cpGroup g) { group = g; }

        virtual cpLayers getLayers () const { return layers; }
        virtual void setLayers (cpLayers l) { layers = l; }

/*--------------------------------------------------------------------------*/

        Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const;
        bool contains (Geometry::Point const &p) const;
        Geometry::Point computeCenter () const;

/*--------------------------------------------------------------------------*/

        VertexBuffer getVertexBuffer () const;

private:

        CPLineStringImpl *impl;
        float radius;
        bool sensor;
        double elasticity;
        double friction;
        cpCollisionType collisionType;
        cpGroup group;
        cpLayers layers;

        E_ (CPLineString)

};

} /* namespace Model */
#endif /* LINESTRING_H_ */
#endif
