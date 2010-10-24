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
#include <Machine.h>

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
        Ptr <StateMachine::Machine> machine = vcast <Ptr <StateMachine::Machine> > (container->getBean ("machine"));

        // To by się mogło ustawiać w kontenerze.
        app->setMainContainer (container);

        // Uruchamiamy dopiero po *calkowitym* zainstancjonowaniu się kontenera, gdyż maszyna ładuje zależne od niego XMLe.
        machine->runOnce ();

        app->loop ();
        return EXIT_SUCCESS;
}
