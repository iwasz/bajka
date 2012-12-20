/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_IDEVICE_H_
#define BAJKA_IDEVICE_H_

#include <core/Object.h>
#include <util/ReflectionMacros.h>

namespace Sound {

/**
 * Główna klasa inicjująca system.
 */
class IDevice : public Core::Object {
public:
        d__
        virtual ~IDevice () {}

        /**
         * Inicjuje. Można podać wejściowe dane potrzebne konkretnej implementacji. Na androidzie
         * będzie to android_app.
         */
        m_ (init)
        virtual void init () = 0;

        /**
         * Debugowe informacje.
         */
        virtual void printInfo () = 0;
        E_ (IDevice)
};

} /* namespace Sound */
#endif /* IDEVICE_H_ */
