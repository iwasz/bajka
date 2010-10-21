/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cstdlib>
#include <Container.h>
#include <ContainerFactory.h>
// TODO wywalić?
#include <Signal.h>

#include "../Bajka.h"
//#include "Platformer.h"

/**
 * \mainpage PlatformerMain Nazwa kodowa : platformer.
 * Jest to próba zrobienia pierwszej platformówki. Tileset, tile jednakowej wielkości,
 * skaczemy hop hop.
 */

/**
 * Main. Ładuje plik cfg/main.xml, wyciąga bean o nazwie app, uruchamia pętlę programu.
 */
int main (int argc, char **argv)
{
        Ptr <Container2::BeanFactoryContainer> container = Container2::XmlContainerFactory::createContainer ("cfg/main.xml", true);
        //        Ptr <PlatformerApp> app = vcast <Ptr <PlatformerApp> > (container->getBean ("app"));
        Ptr <Util::BajkaApp> app = vcast <Ptr <Util::BajkaApp> > (container->getBean ("app"));
        app->loop ();
        return EXIT_SUCCESS;
}
