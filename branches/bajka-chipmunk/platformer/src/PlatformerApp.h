/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef PLATFORMERAPP_H_
#define PLATFORMERAPP_H_

#include <Reflection.h>
#include "../../util/BajkaApp.h"

namespace Container2 {
class BeanFactoryContainer;
}

class PlatformerApp : public Util::BajkaApp {
public:

        __c (void)
        _b ("BajkaApp")

        PlatformerApp () : doLoad (false) {}
        virtual ~PlatformerApp () {}

        /**
         * Ładuje xml i podmienia "główny" kontroler.
         */
        _m (load) void load (Core::String const &xmlFile, Core::String const &controller);

        Ptr <Container2::BeanFactoryContainer> getMainContainer () { return mainContainer; }
        void setMainContainer (Ptr <Container2::BeanFactoryContainer> c) { mainContainer = c; }

        void afterEvents ();

private:

        bool doLoad;
        Core::String xmlFile;
        Core::String controller;

private:

        Ptr <Container2::BeanFactoryContainer> mainContainer;
        Ptr <Container2::BeanFactoryContainer> levelContainer;


        _e (PlatformerApp)
};

#	endif /* PLATFORMERAPP_H_ */
