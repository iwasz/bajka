/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SOUNDEXCEPTION_H_
#define BAJKA_SOUNDEXCEPTION_H_

#include <core/Exception.h>

namespace Sound {

struct SoundException : public Core::Exception {

        SoundException (std::string const &s = "") : Core::Exception (s) {}
        virtual ~SoundException () throw () {}
};

}

#endif /* SOUNDEXCEPTION_H_ */
