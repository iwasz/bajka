/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Device.h"
#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <vector>
#include <string>

/****************************************************************************/

void Device::init ()
{
        // Initialization
        ALCdevice *device = alcOpenDevice (NULL); // select the "preferred device"

        if (device) {
                ALCcontext *context = alcCreateContext (device, NULL);

                if (context) {
                        alcMakeContextCurrent (context);
                }
        }

        alGetError(); // clear error code

        ALuint *buffers = new ALuint[buffersNum];
        alGenBuffers (buffersNum, buffers);
        ALenum error;

        if ((error = alGetError()) != AL_NO_ERROR) {
                printf ("%s : %s", "alGenBuffers", alGetString (error));
                return;
        }
}

/****************************************************************************/

void Device::destroy ()
{

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
