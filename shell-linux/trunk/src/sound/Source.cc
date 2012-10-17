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
        ALenum error;

        if ((error = alGetError ()) != AL_NO_ERROR) {
                throw Sound::SoundException ("Source::Source () : alGenSources : " + std::string (alGetString (error)));
        }
}

/****************************************************************************/

Source::~Source ()
{
        delete impl;
}

/****************************************************************************/

void Source::play (std::string const &bufferName)
{

}

/****************************************************************************/

void Source::play ()
{
        assertThrow (buffer, "Source::play () needs buffer to play. Set it using setBuffer method.");

        alSourcei (impl->source, AL_BUFFER, buffer->getSystemId ());
        ALenum error;

        if ((error = alGetError()) != AL_NO_ERROR) {
                throw Sound::SoundException ("Source::play () : alSourcei (AL_BUFFER) : " + std::string (alGetString (error)));
        }

        alSourcePlay (impl->source);

        if ((error = alGetError()) != AL_NO_ERROR) {
                throw Sound::SoundException ("Source::play () : alSourcei (AL_BUFFER) : " + std::string (alGetString (error)));
        }
}
