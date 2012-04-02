/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "../util/App.h"
#include <cstdlib>
#include <Container.h>
#include <ContainerFactory.h>
#include <inputFormat/mxml/MXmlMetaService.h>
#include "TiliaeModelManager.h"
#include "LoadButtonController.h"

using namespace Container;

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
                fileName = "mail-sorter/main.xml";
        }

        try {
                Ptr <Container::BeanFactoryContainer> container = ContainerFactory::createContainer (MXmlMetaService::parseFile (fileName), true);
                Ptr <Util::App> app = vcast <Ptr <Util::App> > (container->getBean ("app"));
                app->setInstance (app.get ());

                // TODO to się powinno samo ustawiać w XML.
                Util::TiliaeModelManager *manager = vcast <Util::TiliaeModelManager *> (container->getBean ("modelManager"));
                manager->setMainContainer (container);
                manager->play ("menu");

                app->init ();
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
