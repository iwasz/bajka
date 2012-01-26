/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "../util/BajkaApp.h"
#include <cstdlib>
#include <Container.h>
#include <ContainerFactory.h>

/**
 * Main entry.
 */
int main (int argc, char **argv)
{
        std::string fileName;

        if (argc > 1) {
                fileName = *(argv + 1);
        }
        else {
                fileName = "examples/chipmunk.xml";
        }

        // Nie robimy try-catch, bo i tak info zostanie wypisane.
        Ptr <Container::BeanFactoryContainer> container = Container::XmlContainerFactory::createContainer (fileName, true);
        Ptr <Util::BajkaApp> app = vcast <Ptr <Util::BajkaApp> > (container->getBean ("app"));

        try {
                app->loop ();
                app->destroy ();
        }
        catch (std::exception const &e) {
                std::cerr << "Exception caught : " << e.what () << std::endl;
        }
        catch (...) {
                std::cerr << "Unknown exception." << std::endl;
        }


        return EXIT_SUCCESS;
}
