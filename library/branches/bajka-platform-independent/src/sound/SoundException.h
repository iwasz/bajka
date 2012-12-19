/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA1_SOUNDEXCEPTION_H_
#define BAJKA1_SOUNDEXCEPTION_H_

#include <core/Exception.h>

namespace Sound {

struct SoundException : public Core::Exception {

        SoundException (std::string const &s = "") : Core::Exception (s) {}
        virtual ~SoundException () throw () {}
};

}

/**
 *
 */
//extern void soundThrow (std::string const &msg);

#endif /* SOUNDEXCEPTION_H_ */
