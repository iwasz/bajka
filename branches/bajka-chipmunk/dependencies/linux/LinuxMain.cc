/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef LINUX
#include "../util/App.h"
#include <cstdlib>
#include <Container.h>
#include <ContainerFactory.h>
#include <inputFormat/mxml/MXmlMetaService.h>
#include "TiliaeModelManager.h"

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

                Util::TiliaeModelManager *manager = vcast <Util::TiliaeModelManager *> (container->getBean ("modelManager"));
                // TODO to się powinno samo ustawiać w XML.
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
#endif



