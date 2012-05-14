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

#ifdef USE_SDL
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>
#endif

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
                fileName = "main.xml";
        }

        try {

#ifdef USE_SDL
                /* Initialize SDL for video output */
                if (SDL_Init (SDL_INIT_VIDEO) < 0) {
                        throw Util::InitException ("Unable to initialize SDL : " + std::string (SDL_GetError ()));
                }

                if (TTF_Init () < 0) {
                        throw Util::InitException ("TTF_Init failed");
                }
#endif

                Ptr <Container::BeanFactoryContainer> container = ContainerFactory::createContainer (MXmlMetaService::parseFile (fileName), true);
                Ptr <Util::App> app = vcast <Ptr <Util::App> > (container->getBean ("app"));
                app->setInstance (app.get ());

//                Util::TiliaeModelManager *manager = vcast <Util::TiliaeModelManager *> (container->getBean ("modelManager"));
//                // TODO to się powinno samo ustawiać w XML.
//                manager->setMainContainer (container);
//                manager->play ("menu");

                app->init ();
                app->loop ();
                app->destroy ();

#ifdef USE_SDL
                TTF_Quit ();
                SDL_Quit ();
#endif
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
