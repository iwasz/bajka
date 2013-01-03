/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef WITH_CHIPMUNK
#ifndef BAJKA_MODEL_CP_ISHAPE_H_
#define BAJKA_MODEL_CP_ISHAPE_H_

#include <chipmunk.h>
#include "util/ReflectionMacros.h"
#include "model/IModel.h"

namespace Model {
class Body;

class ICPShape : public virtual Core::Object {
public:

        d__

        virtual ~ICPShape () {}

        virtual cpBody *getCPBody () = 0;
        virtual Body *getBody () = 0;

        virtual bool getSensor () const = 0;
        m_ (setSensor) virtual void setSensor (bool b) = 0;

        virtual double getElasticity () const = 0;
        m_ (setElasticity) virtual void setElasticity (double e) = 0;

        virtual double getFriction () const = 0;
        m_ (setFriction) virtual void setFriction (double d) = 0;

        virtual Geometry::Point getSurfaceVelocity () const = 0;
        m_ (setSurfaceVelocity) virtual void setSurfaceVelocity (Geometry::Point const &) = 0;

        virtual cpCollisionType getCollisionType () const = 0;
        virtual void setCollisionType (cpCollisionType ct) = 0;

        virtual cpGroup getGroup () const = 0;
        virtual void setGroup (cpGroup g) = 0;

        virtual cpLayers getLayers () const = 0;
        virtual void setLayers (cpLayers l) = 0;

        E_ (ICPShape)
};

} /* namespace Model */

#endif /* SHAPE_H_ */
#endif
