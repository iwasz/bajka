/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Source.h"
#include <AL/al.h>
#include <AL/alc.h>
#include "SoundException.h"
#include <util/Exceptions.h>

/****************************************************************************/

struct Source::Impl {

        Impl () : source (0) {}

        ALuint source;
};

/****************************************************************************/

Source::Source () : impl (new Impl)
{
        // Generate Sources
        alGenSources (1, &impl->source);
        soundThrow ("Source::Source () : alGenSources : ");
}

/****************************************************************************/

Source::~Source ()
{
        stop ();
        alDeleteSources (1, &impl->source);
        assert (alGetError () == AL_NO_ERROR);
        delete impl;
}

/****************************************************************************/

void Source::play (std::string const &bufferName)
{
        assertThrow (device, "Source::play (s) device is NULL");
        play (device->getBuffer (bufferName));
}

/****************************************************************************/

void Source::play ()
{
        play (buffer);
}

/****************************************************************************/

void Source::play (Buffer *buf)
{
        assertThrow (buffer, "Source::play () needs buffer to play. Set it using setBuffer method.");

        ALint i;
        alGetSourcei (impl->source, AL_SOURCE_STATE, &i);
        soundThrow ("Source::play : alGetSourcei (AL_SOURCE_STATE) : ");

        if (i == AL_PLAYING) {
                return;
        }

        alSourcei (impl->source, AL_BUFFER, buffer->getSystemId ());
        soundThrow ("Source::play () : alSourcei (AL_BUFFER) : ");
        alSourcePlay (impl->source);
        soundThrow ("Source::play () : alSourcePlay () : ");
}

/****************************************************************************/

void Source::pause ()
{
        alSourcePause (impl->source);
        soundThrow ("Source::pause () : alSourcePause () : ");
}

/****************************************************************************/

void Source::stop ()
{
        alSourceStop (impl->source);
        soundThrow ("Source::stop () : alSourceStop () : ");
}

/****************************************************************************/

void Source::rewind ()
{
        alSourceRewind (impl->source);
        soundThrow ("Source::rewind () : alSourceRewind () : ");
}

/****************************************************************************/

float Source::getGain () const
{
        float f;
        alGetSourcef (impl->source, AL_GAIN, &f);
        soundThrow ("Source::getGain : alGetSourcef : ");
        return f;
}

/****************************************************************************/

void Source::setGain (float f)
{
        alSourcef (impl->source, AL_GAIN, f);
        soundThrow ("Source::setGain : alSourcef : ");
}

/****************************************************************************/

float Source::getPitch () const
{
        float f;
        alGetSourcef (impl->source, AL_PITCH, &f);
        soundThrow ("Source::getPitch : alGetSourcef : ");
        return f;
}

/****************************************************************************/

void Source::setPitch (float f)
{
        alSourcef (impl->source, AL_PITCH, f);
        soundThrow ("Source::setPitch : alSourcef : ");
}

/****************************************************************************/

float Source::getOffset () const
{
        float f;
        alGetSourcef (impl->source, AL_SEC_OFFSET, &f);
        soundThrow ("Source::getOffset : alGetSourcef : ");
        return f;
}

/****************************************************************************/

void Source::setOffset (float f)
{
        alSourcef (impl->source, AL_SEC_OFFSET, f);
        soundThrow ("Source::setOffset : alSourcef : ");
}

/****************************************************************************/

Geometry::Point3 Source::getPosition () const
{
        Geometry::Point3 p = {0, 0, 0};
        alGetSourcefv (impl->source, AL_POSITION, &p.x);
        soundThrow ("Source::getPosition : alGetSourcefv : ");
        return p;
}

/****************************************************************************/

void Source::setPosition (Geometry::Point3 &p)
{
        alSourcefv (impl->source, AL_POSITION, &p.x);
        soundThrow ("Source::setPosition : alSourcefv : ");
}

/****************************************************************************/

Geometry::Point3 Source::getVelocity () const
{
        Geometry::Point3 p = {0, 0, 0};
        alGetSourcefv (impl->source, AL_VELOCITY, &p.x);
        soundThrow ("Source::getVelocity : alGetSourcefv : ");
        return p;
}

/****************************************************************************/

void Source::setVelocity (Geometry::Point3 &p)
{
        alSourcefv (impl->source, AL_VELOCITY, &p.x);
        soundThrow ("Source::setVelocity : alSourcefv : ");
}

/****************************************************************************/

Geometry::Point3 Source::getDirection () const
{
        Geometry::Point3 p = {0, 0, 0};
        alGetSourcefv (impl->source, AL_DIRECTION, &p.x);
        soundThrow ("Source::getDirection : alGetSourcefv : ");
        return p;
}

/****************************************************************************/

void Source::setDirection (Geometry::Point3 &p)
{
        alSourcefv (impl->source, AL_DIRECTION, &p.x);
        soundThrow ("Source::setDirection : alSourcefv : ");
}

/****************************************************************************/

bool Source::getLooping () const
{
        int i;
        alGetSourcei (impl->source, AL_LOOPING, &i);
        soundThrow ("Source::getLooping : alGetSourcei : ");
        return i;
}

/****************************************************************************/

void Source::setLooping (bool b)
{
        alSourcei (impl->source, AL_LOOPING, b);
        soundThrow ("Source::setLooping : alSourcei : ");
}
