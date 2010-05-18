/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "Image.h"
#include "Model.h"
#include "Events.h"
#include "Util.h"
#include "OpenGL.h"

#include "sequence/Sequence.h"
#include "mapping/Mapping.h"

#include "Sdl.h"
#include "View.h"

#include "BajkaApp.h"
#include "Controller.h"
#include "Model.h"

// TODO Gdzieś to przenieść, coś wymyślić. Moze też do kontenera, a może to będzie stałe.
Ptr <Sdl::EventDispatcher> sdlDispatcher;
Ptr <Events::MouseButtonDispatcher> mouseButtonDispatcher;
Ptr <Events::MouseMotionDispatcher> mouseMotionDispatcher;
Ptr <Events::MouseMotionDispatcher> mouseMotionScreenMargin;
Ptr <Sdl::TimerDispatcher> timeDispatcher;

namespace Util {
namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace R = Reflection;

/****************************************************************************/

BajkaConfig::BajkaConfig () : fullScreen (false), resX (640), resY (480), windowCaption ("BajkaApp")
{
}

/****************************************************************************/

void BajkaConfig::init ()
{
        /* Initialize SDL for video output */
        if (SDL_Init (SDL_INIT_VIDEO) < 0) {
                fprintf (stderr, "Unable to initialize SDL: %s\n", SDL_GetError ());
                exit (1);
        }

        int flags;
        if (fullScreen) {
            flags = SDL_OPENGL | SDL_FULLSCREEN;
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE,   8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,  8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,  8);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        }
        else {
                flags = SDL_OPENGL;
        }

        /* Create a 640x480 OpenGL screen */
        if (SDL_SetVideoMode (resX, resY, 0, flags) == NULL) {
                fprintf (stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError ());
                SDL_Quit ();
                exit (2);
        }

        /* Set the title bar in environments that support it */
        SDL_WM_SetCaption (windowCaption.c_str (), NULL);

/*##########################################################################*/

        glShadeModel(GL_FLAT);
        glDisable (GL_DEPTH_TEST);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        /*
         * Alpha blending. Niestety tekstura jest w niektorych miejscach
         * przezroczysta, ale wystaje spodniej niebieski kolor prostokątu.
         */
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        /*--------------------------------------------------------------------------*/
        #define TRY_CATCH

        #if defined (TRY_CATCH)
                try {
        #endif
//                        container = Container2::XmlContainerFactory::createContainer ("main2.xml");
        //                image01Ctr = vcast <Ptr <C::SimpleController> > (container->getBean ("cursor"));
        //                sniezynkaCtr = vcast <Ptr <SnowflakeController> > (container->getBean ("snowFlake"));
//                        screenCtr = vcast <Ptr <C::SimpleController> > (container->getBean ("screen"));

        /*--------------------------------------------------------------------------*/

        //                image01 = dynamic_pointer_cast <M::AbstractModel> (image01Ctr->getModel ());
        //                sniezynka = dynamic_pointer_cast <M::AbstractModel> (sniezynkaCtr->getModel ());

        /*##########################################################################*/

                        sdlDispatcher = Ptr <Sdl::EventDispatcher> (new Sdl::EventDispatcher ());
                        mouseButtonDispatcher = Ptr <Events::MouseButtonDispatcher> (new Events::MouseButtonDispatcher ());
                        mouseMotionDispatcher = Ptr <Events::MouseMotionDispatcher> (new Events::MouseMotionDispatcher ());
                        mouseMotionScreenMargin = Ptr <Events::MouseMotionDispatcher> (new Events::MouseMotionDispatcher ());
                        timeDispatcher = Ptr <Sdl::TimerDispatcher> (new Sdl::TimerDispatcher ());

                        sdlDispatcher->Events::AbstractObservable <Events::MouseMotionEvent>::addObserver (mouseMotionScreenMargin);

                        // To powinno iść ze screen (screen->getViewPort, albo coś).
                        // TODO to będzie zorganizowane inaczej, będą marginesy.
                        mouseMotionScreenMargin->setArea (Geometry::Box (1, 1, 638, 478));
                        mouseMotionScreenMargin->setMode (Events::MouseMotionDispatcher::OUT);

                        timeDispatcher->setTickInterval (15);
        //                timeDispatcher->addObserver (sniezynkaCtr);

        #if defined (TRY_CATCH)
                }
                catch (const Core::Exception &e) {
                        std::cerr << e.getMessage () << std::endl;
                        exit (1);
                }
                catch (...) {
                        std::cerr << "Unknown exception" << std::endl;
                        exit (1);
                }
        #endif

        /*##########################################################################*/

                // Transformacje.
                glViewport (0, 0, (GLsizei) resX, (GLsizei) resY);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                // gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
                gluOrtho2D (-resX/2, resX/2, -resY/2, resY/2);

                glMatrixMode(GL_MODELVIEW);
                glLoadIdentity();

                GLfloat params[100];
                glGetFloatv (GL_ALIASED_POINT_SIZE_RANGE, params);
                std::cerr << "GL_ALIASED_POINT_SIZE_RANGE : " << params[0] << ", " << params[1] << std::endl;

                glGetFloatv (GL_SMOOTH_POINT_SIZE_RANGE, params);
                std::cerr << "GL_SMOOTH_POINT_SIZE_RANGE : " << params[0] << ", " << params[1] << std::endl;

                glGetFloatv (GL_SMOOTH_POINT_SIZE_GRANULARITY, params);
                std::cerr << "GL_SMOOTH_POINT_SIZE_GRANULARITY : " << params[0] << ", " << params[1] << std::endl;

                glDisable (GL_POINT_SMOOTH);
                std::cerr << "is enabled GL_POINT_SMOOTH : " << ((glIsEnabled (GL_POINT_SMOOTH)) ? ("true") : ("false")) << std::endl;

                glPointSize (3);
                glGetFloatv (GL_POINT_SIZE, params);
                std::cerr << "GL_POINT_SIZE : " << params[0] << std::endl;
}

/*##########################################################################*/

void BajkaApp::run (int argc, char **argv)
{

}

/****************************************************************************/

void BajkaApp::loop ()
{
        bool done = false;

        while (!done) {

                timeDispatcher->run ();

                SDL_Event event;

                // To do wywalenia.
                while (SDL_PollEvent (&event)) {

                        sdlDispatcher->run (&event);


                        if (event.type == SDL_QUIT) {
                                done = 1;
                        }
                        if (event.type == SDL_KEYDOWN) {
                                if (event.key.keysym.sym == SDLK_ESCAPE) {
                                        done = 1;
                                }
                        }

                }

                rootController->draw ();

                // Tak śmiga, że damy delay
                SDL_Delay (5);
        }
}

/****************************************************************************/

void BajkaApp::destroy ()
{
        std::cerr << "gl version : " << glGetString(GL_VERSION) << std::endl;

        int i;
        glGetIntegerv (GL_MAX_TEXTURE_SIZE, &i);
        std::cerr << "max texture size : " << i << std::endl;

        SDL_Quit ();
}

} // Nam
