/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <AL/al.h>
#include "SoundException.h"

void soundThrow (std::string const &msg)
{
        ALenum error;

        if ((error = alGetError ()) != AL_NO_ERROR) {
                throw Sound::SoundException (msg + alGetString (error));
        }
}
