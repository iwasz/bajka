/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_SOURCE_H_
#define BAJKA_SHELL_SOURCE_H_

#include <util/ReflectionMacros.h>
#include "Device.h"
#include "Buffer.h"

class Source {
public:
        C__ (void)

        Source ();
        virtual ~Source ();

        void play (std::string const &bufferName);
        void play ();

private:

        struct Impl;
        Device *p_(device)
        Buffer *p_(buffer)
        Impl *impl;

        E_ (Source)
};

#endif /* SOURCE_H_ */
