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
        void setGain (float f);

        Geometry::Point3 getPosition () const;
        void setPosition (Geometry::Point3 &p);

        Geometry::Point3 getVelocity () const;
        void setVelocity (Geometry::Point3 &p);

        Geometry::Point3 getAt () const;
        void setAt (Geometry::Point3 &p);

        Geometry::Point3 getUp () const;
        void setUp (Geometry::Point3 &p);
};

#endif /* LISTENER_H_ */
