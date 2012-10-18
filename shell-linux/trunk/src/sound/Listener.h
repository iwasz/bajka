/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_LISTENER_H_
#define BAJKA_SHELL_LISTENER_H_

#include <geometry/Point3.h>
#include <util/ReflectionMacros.h>

class Listener {
public:
        C__ (void)

        virtual ~Listener () {}

        float getGain () const;
        m_ (setGain) void setGain (float f);

        Geometry::Point3 getPosition () const;
        m_ (setPosition) void setPosition (Geometry::Point3 &p);

        Geometry::Point3 getVelocity () const;
        m_ (setVelocity) void setVelocity (Geometry::Point3 &p);

        Geometry::Point3 getAt () const;
        m_ (setAt) void setAt (Geometry::Point3 &p);

        Geometry::Point3 getUp () const;
        m_ (setUp) void setUp (Geometry::Point3 &p);

        E_ (Listener)
};

#endif /* LISTENER_H_ */
