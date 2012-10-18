/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_SOURCE_H_
#define BAJKA_SHELL_SOURCE_H_

#include <util/ReflectionMacros.h>
#include "Device.h"
#include "Buffer.h"
#include <geometry/Point3.h>

class Source {
public:
        C__ (void)

        Source ();
        virtual ~Source ();

        void play (std::string const &bufferName);
        void play ();
        void pause ();
        void stop ();
        void rewind ();

        float getGain () const;
        m_ (setGain) void setGain (float f);

        float getPitch () const;
        m_ (setPitch) void setPitch (float f);

        float getOffset () const;
        m_ (setOffset) void setOffset (float f);

        Geometry::Point3 getPosition () const;
        m_ (setPosition) void setPosition (Geometry::Point3 &p);

        Geometry::Point3 getVelocity () const;
        m_ (setVelocity) void setVelocity (Geometry::Point3 &p);

        Geometry::Point3 getDirection () const;
        m_ (setVelocity) void setDirection (Geometry::Point3 &p);

        bool getLooping () const;
        m_ (setLooping) void setLooping (bool b);

private:

        void play (Buffer *buf);

private:

        struct Impl;
        Device *p_(device)
        Buffer *p_(buffer)
        Impl *impl;

        E_ (Source)
};

#endif /* SOURCE_H_ */
