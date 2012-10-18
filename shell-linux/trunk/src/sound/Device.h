/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_DEVICE_H_
#define BAJKA_SHELL_DEVICE_H_

#include <util/ReflectionMacros.h>

class Buffer;

/**
 * Inicjuje / zamyka OpenAl i jest managerem buforów.
 */
class Device {
public:

        C__ (void)

        Device ();
        virtual ~Device ();

        m_ (init) void init ();
        void printInfo ();

private:

        class Impl;
        friend class Buffer;
        friend class Source;
        void registerBuffer (std::string const &name, Buffer *);
        void unregisterBuffer (std::string const &name);
        Buffer *getBuffer (std::string const &name);

private:

        int p_ (buffersNum)
        Impl *impl;

        E_ (Device)
};

#endif /* DEVICE_H_ */
