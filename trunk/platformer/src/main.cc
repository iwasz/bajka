/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <cstdlib>
#include "IWidget.h"

#include <Container.h>
#include <ContainerFactory.h>

#include "BajkaApp.h"
#include "sequence/ConstSequence.h"

// TODO wywalić
#include <Signal.h>
#include "PlatformerApp.h"

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
        Ptr <PlatformerApp> app = vcast <Ptr <PlatformerApp> > (container->getBean ("app"));
        // To by się mogło ustawiać w kontenerze.
        app->setMainContainer (container);
        app->loop ();
        return EXIT_SUCCESS;
}
