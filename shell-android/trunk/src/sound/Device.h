/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_DEVICE_H_
#define BAJKA_SHELL_DEVICE_H_

#include <sound/IDevice.h>
#include <string>
#include <android_native_app_glue.h>

class Buffer;
class SoundContext;

/**
 * Inicjuje / zamyka OpenSL ES.
 */
class Device : public Sound::IDevice {
public:

        C__ (void)
        b_ ("IDevice")

        Device ();
        virtual ~Device ();

        void init ();
        void printInfo ();
        m_ (setAndroidApp) void setAndroidApp (android_app *app);

        /*
         * No a part of an API.
         */
        SoundContext *getSoundContext ();

private:

        struct Impl;
        Impl *impl;

        E_ (Device)
};

#endif /* DEVICE_H_ */
