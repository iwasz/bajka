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

#include "BajkaApp.h"

/**
 * Main entry.
 */
int main (int argc, char **argv)
{
        // Nie roine try-catch, bo i tak info zostanie wypisane.
        Ptr <Container2::BeanFactoryContainer> container = Container2::XmlContainerFactory::createContainer ("main2.xml");
        Ptr <Util::BajkaApp> app = vcast <Ptr <Util::BajkaApp> > (container->getBean ("app"));

        app->run (argc, argv);
        app->loop ();
        app->destroy ();
        return EXIT_SUCCESS;
}
