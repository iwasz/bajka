/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef DEVICE_H_
#define DEVICE_H_

#include <util/ReflectionMacros.h>

class Device {
public:

        C__ (void)

        Device () : buffersNum (10) {}
        virtual ~Device () {}

        m_ (init) void init ();
        void destroy ();
        void printInfo ();

private:

        int p_ (buffersNum)

        E_ (Device)
};

#endif /* DEVICE_H_ */
