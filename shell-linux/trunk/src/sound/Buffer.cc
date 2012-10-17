/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Buffer.h"
#include <AL/alut.h>
#include "SoundException.h"
#include <util/Exceptions.h>

/****************************************************************************/

struct Buffer::Impl {

        Impl () : buffer (0) {}

        ALuint buffer;
        std::string name;
};

/****************************************************************************/

Buffer::Buffer ()
{
        impl = new Impl;

#if 0
        alGetError(); // clear error code
        alGenBuffers (1, &impl->buffer);
        ALenum error;

        if ((error = alGetError()) != AL_NO_ERROR) {
                throw Sound::SoundException ("Buffer::Buffer () : alGenBuffers : " + std::string (alGetString (error)));
        }
#endif
}

/****************************************************************************/

Buffer::~Buffer ()
{
        alDeleteBuffers (1, &impl->buffer);
        delete impl;
}

/****************************************************************************/

void Buffer::setLoad (std::string const &path)
{
        alutGetError ();
        impl->buffer = alutCreateBufferFromFile (path.c_str ());

        if (impl->buffer == AL_NONE) {
                throw Sound::SoundException ("Buffer::setLoad () : alutCreateBufferFromFile : " + std::string (alutGetErrorString (alutGetError ())));
        }
}

/****************************************************************************/

void Buffer::setName (std::string const &name)
{
        impl->name = name;
        assertThrow (device, "Buffer::setName : device must be set prior to calling this method.");
        device->unregisterBuffer (name);
        device->registerBuffer (name, this);
}

/****************************************************************************/

std::string const &Buffer::getName () const
{
        return impl->name;
}

/****************************************************************************/

unsigned int Buffer::getSystemId () const
{
        return impl->buffer;
}
