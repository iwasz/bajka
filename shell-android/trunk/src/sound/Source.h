/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_SOURCE_H_
#define BAJKA_SHELL_SOURCE_H_

#include "Device.h"
#include "Buffer.h"
#include <sound/ISource.h>

/**
 *
 */
class Source : public Sound::ISource {
public:
        C__ (void)
        b_ ("ISource")

        Source ();
        virtual ~Source ();

        void play (std::string const &bufferName);
        void play ();
        void pause ();
        void stop ();
        void rewind ();

        float getGain () const;
        void setGain (float f);

        float getPitch () const;
        void setPitch (float f);

        float getOffset () const;
        void setOffset (float f);

        Geometry::Point3 getPosition () const;
        void setPosition (Geometry::Point3 &p);

        Geometry::Point3 getVelocity () const;
        void setVelocity (Geometry::Point3 &p);

        Geometry::Point3 getDirection () const;
        void setDirection (Geometry::Point3 &p);

        bool getLooping () const;
        void setLooping (bool b);

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
