/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_SOURCE_H_
#define BAJKA_SHELL_SOURCE_H_

#include <sound/ISource.h>

namespace Sound {
class IDevice;
class IBuffer;
}

/**
 *
 */
class Source : public Sound::ISource {
public:
        C__ (void)
        b_ ("ISource")

        Source ();
        virtual ~Source ();

        m_ (init)
        void init ();
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

        void play (Sound::IBuffer *buf);

private:

        struct Impl;
        Sound::IDevice *p_(device)
        Sound::IBuffer *p_(buffer)
        Impl *impl;

        E_ (Source)
};

#endif /* SOURCE_H_ */
