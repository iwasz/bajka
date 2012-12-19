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
 *
 */
class Buffer : public Sound::IBuffer {
public:
        C__ (void)

        Buffer ();
        virtual ~Buffer ();

        /**
         * Ładuje plik wav.
         */
        m_ (setLoad) void setLoad (std::string const &path);

        /**
         * Nazwa pod jaką ten bufor będzie dostepny dla źródeł.
         */
        m_ (setName) void setName (std::string const &name);
        std::string const &getName () const;

        /**
         * Platform dependent - moze inny typ?
         */
        unsigned int getSystemId () const;

private:

        struct Impl;
        Device *p_(device)
        Impl *impl;

        E_ (Buffer)
};

typedef std::map <std::string, Buffer *> BufferMap;

#endif /* BUFFER_H_ */
