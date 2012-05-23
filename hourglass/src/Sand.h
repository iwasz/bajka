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
 * Model reprezentujący pewną objetość piasku, która początkowo ma wymiary width i height (ma postać
 * prostokąta). Kazde ziarno jest osobnym obiektem chipmunkowym i ma swoją masę (mass) i inne własciwości.
 */
class Sand : public Model::AbstractModel, public Model::IVertexBufferEnabled {
public:

        C__ (void)
        b_ ("AbstractModel")

        Sand ();
        virtual ~Sand();

        m_ (init) void init ();

/*--------------------------------------------------------------------------*/

        Geometry::Box getBoundingBoxImpl (Geometry::AffineMatrix const &transformation) const;
        bool contains (Geometry::Point const &p) const;
        Geometry::Point computeCenter () const;

/*--------------------------------------------------------------------------*/

        Model::VertexBuffer getVertexBuffer () const;

        m_ (setWidth) void setWidth (float w) { width = w; }
        m_ (setHeight) void setHeight (float h) { height = h; }
        m_ (setGrainNo) void setGrainNo (int g) { grainNo = g; }
        m_ (setRadius) void setRadius (float r) { radius = r; }
        m_ (setMass) void setMass (float m) { mass = m; }
        m_ (setElasticity) void setElasticity (float e) { elasticity = e; }
        m_ (setFriction) void setFriction (float f) { friction = f; }
        m_ (setLl) void setLl (Geometry::Point const &p) { ll = p; }

private:

        void addGrain (int i, int j, float densityX, float densityY, int cnt);

private:

        SandImpl *impl;
        float width;
        float height;
        int grainNo;
        float radius;
        float mass;
        float elasticity;
        float friction;
        Geometry::Point ll;

        E_ (Sand)

};

#endif
