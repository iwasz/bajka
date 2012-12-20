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
 * Specjalny typ źródła, który działa bez bufora. Sam ładuje sobie plik muzyczny i go odtwarza.
 * Na androidzie potrafi sam zdekodować mp3 i inne formaty.(na 99% od API LEVEL-9).
 * TODO Musi implementować interfejs ISource.
 */
class BackgroundMusicSource : public Sound::IBuffer {
public:
        C__ (void)
        b_ ("IBuffer")

        BackgroundMusicSource ();
        virtual ~BackgroundMusicSource ();

        /**
         * Ładuje plik wav.
         */
        void setLoad (std::string const &path);

        /**
         * Nazwa pod jaką ten bufor będzie dostepny dla źródeł.
         */
        void setName (std::string const &name);
        std::string const &getName () const;

private:

        struct Impl;
        Device *p_(device)
        Impl *impl;

        E_ (Buffer)
};

typedef std::map <std::string, Buffer *> BufferMap;

#endif /* BUFFER_H_ */
