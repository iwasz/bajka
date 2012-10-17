/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Device.h"
#include <iostream>
#include <AL/alut.h>
#include <vector>
#include <string>
#include "SoundException.h"
#include "Buffer.h"

/****************************************************************************/

struct Device::Impl {
        BufferMap buffers;
};

/****************************************************************************/

Device::Device () : buffersNum (7), impl (new Impl) {}

/****************************************************************************/

Device::~Device ()
{
        assert (alutExit ());

#if 0
        ALCcontext *context = alcGetCurrentContext ();
        ALCdevice *device = alcGetContextsDevice (context);
        alcMakeContextCurrent (NULL);
        alcDestroyContext (context);
        alcCloseDevice (device);
#endif

        delete impl;
}

/****************************************************************************/

void Device::init ()
{
#if 0
        // Initialization
        ALCdevice *device = alcOpenDevice (NULL); // select the "preferred device"

        if (device) {
                ALCcontext *context = alcCreateContext (device, NULL);

                if (context) {
                        alcMakeContextCurrent (context);
                }
        }
#endif

        if (!alutInit (NULL, NULL)) {
                throw Sound::SoundException ("Device::init () : alutInit : " + std::string (alutGetErrorString (alutGetError ())));
        }
}

/****************************************************************************/

void Device::printInfo ()
{
        if (alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT") == AL_TRUE) {
                std::cout << "ALC_ENUMERATION_EXT present... Available devices :" << std::endl;
        }

/*--------------------------------------------------------------------------*/

        const ALCchar *devices = alcGetString (NULL, ALC_DEVICE_SPECIFIER);
        const ALCchar *defaultDeviceName = alcGetString (NULL, ALC_DEFAULT_DEVICE_SPECIFIER);

        char nullCnt = 0;
        typedef std::vector <std::string> Vec;
        Vec deviceNames;
        std::string tmp;
        ALCchar c = '\0';

        while (true) {
                c = *devices++;
                nullCnt += (!c);
                nullCnt = ((c) ? (0) : (nullCnt));

                if (nullCnt >= 2) {
                        break;
                }

                if (!c) {
                        deviceNames.push_back (tmp);
                        tmp.clear ();
                        break;
                }

                tmp += c;
        }

        for (Vec::const_iterator i = deviceNames.begin (); i != deviceNames.end (); ++i) {
                std::cout << "  " << *i;

                if (*i == defaultDeviceName) {
                        std::cout << " [default]";
                }

                std::cout << std::endl;
        }
}

/****************************************************************************/

void Device::registerBuffer (std::string const &name, Buffer *b)
{
        impl->buffers[name] = b;
}

/****************************************************************************/

void Device::unregisterBuffer (std::string const &name)
{
        impl->buffers.erase (name);
}

/****************************************************************************/

Buffer *Device::getBuffer (std::string const &name)
{
        BufferMap::iterator i = impl->buffers.find (name);
        return ((i != impl->buffers.end ()) ? (i->second) : (NULL));
}
