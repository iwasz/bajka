/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_LISTENER_H_
#define BAJKA_SHELL_LISTENER_H_

#include <sound/IListener.h>

/**
 * To be implemented in future versions of Android. As for now, this
 * class takes no action at all.
 */
class Listener : public Sound::IListener {
public:
        C__ (void)
        b_ ("IListener")

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

        E_ (Listener)
};

#endif /* LISTENER_H_ */
