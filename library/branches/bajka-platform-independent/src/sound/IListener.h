/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_ITFCES_ILISTENER_H_
#define BAJKA_ITFCES_ILISTENER_H_

#include <geometry/Point3.h>
#include <util/ReflectionMacros.h>

namespace Sound {

/**
 * 3D audio listener.
 */
class IListener {
public:
        d__
        virtual ~IListener () {}

        virtual float getGain () const = 0;
        m_ (setGain) virtual void setGain (float f) = 0;

        virtual Geometry::Point3 getPosition () const = 0;
        m_ (setPosition) virtual void setPosition (Geometry::Point3 &p) = 0;

        virtual Geometry::Point3 getVelocity () const = 0;
        m_ (setVelocity) virtual void setVelocity (Geometry::Point3 &p) = 0;

        virtual Geometry::Point3 getAt () const = 0;
        m_ (setAt) virtual void setAt (Geometry::Point3 &p) = 0;

        virtual Geometry::Point3 getUp () const = 0;
        m_ (setUp) virtual void setUp (Geometry::Point3 &p) = 0;

        E_ (Listener)
};

} /* namespace Sound */
#endif /* ILISTENER_H_ */
