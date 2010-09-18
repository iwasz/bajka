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

/**
 * Main entry.
 */
int main (int argc, char **argv)
{
        // Nie roine try-catch, bo i tak info zostanie wypisane.
        Ptr <Container2::BeanFactoryContainer> container = Container2::XmlContainerFactory::createContainer ("main2.xml");
        Ptr <Util::BajkaApp> app = vcast <Ptr <Util::BajkaApp> > (container->getBean ("app"));

        // TODO Do wywalenia, kiedy beany singleton będą się same instancjonowac.
//        Core::Variant v = container->getBean ("scrollService");

        app->run (argc, argv);
        app->loop ();
        app->destroy ();
        return EXIT_SUCCESS;
}
