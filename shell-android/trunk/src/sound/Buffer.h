/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_BUFFER_H_
#define BAJKA_SHELL_BUFFER_H_

#include "Device.h"
#include <sound/IBuffer.h>

/**
 * Updated the native audio API based on the Khronos Group OpenSL ES 1.0.1? standard.
 * With API Level 14, you can now decode compressed audio (e.g. MP3, AAC, Vorbis) to PCM.
 * For more details, see docs/opensles/index.html and http://www.khronos.org/opensles/.
 */
class Buffer : public Sound::IBuffer {
public:
        C__ (void)
        b_ ("IBuffer")

        Buffer ();
        virtual ~Buffer ();

        /**
         * Ładuje plik wav.
         */
        void setLoad (std::string const &path);

        /**
         * Nazwa pod jaką ten bufor będzie dostepny dla źródeł.
         */
        void setName (std::string const &name);
        std::string const &getName () const;

        void const *getData () const;
        size_t getSize () const;

private:

        struct Impl;
        Device *p_(device)
        Impl *impl;

        E_ (Buffer)
};

typedef std::map <std::string, Buffer *> BufferMap;

#endif /* BUFFER_H_ */
