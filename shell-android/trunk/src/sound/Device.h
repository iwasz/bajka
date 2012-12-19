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

class Buffer;

/**
 * Inicjuje / zamyka OpenSL ES.
 */
class Device : public Sound::IDevice {
public:

        C__ (void)
        b_ ("IDevice")

        virtual ~Device ();

        void init (void *systemData);
        void printInfo ();

private:

        void createAssetAudioPlayer (std::string const &filename);

        Device ();
        friend class ShellFactory;

private:

        struct Impl;
        Impl *impl;

        E_ (Device)
};

#endif /* DEVICE_H_ */
