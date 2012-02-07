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

        try {
                Ptr <Container::BeanFactoryContainer> container = Container::XmlContainerFactory::createContainer (fileName, true);
                Ptr <Util::BajkaApp> app = vcast <Ptr <Util::BajkaApp> > (container->getBean ("app"));

//				app->init ();
                app->loop ();
                app->destroy ();
        }
        catch (Core::Exception const &e) {
                std::cerr << "Exception caught : \n" << e.getMessage () << std::endl;
        }
        catch (std::exception const &e) {
                std::cerr << "exception caught : " << e.what () << std::endl;
        }
        catch (...) {
                std::cerr << "Unknown exception." << std::endl;
        }


        return EXIT_SUCCESS;
}
