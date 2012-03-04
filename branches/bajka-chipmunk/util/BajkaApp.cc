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
#include <SDL_ttf.h>

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <boost/bind.hpp>

#include "Events.h"
#include "BajkaApp.h"
#include "../view/draw/Primitives.h"
#include "../model/IGroup.h"
#include "../tween/Manager.h"
#include "../events/types/UpdateEvent.h"

/****************************************************************************/

Util::BajkaApp *app ()
{
        return Util::BajkaApp::instance ();
}

/****************************************************************************/

Util::BajkaConfig *config ()
{
        return Util::BajkaApp::instance ()->getConfig ().get ();
}

/****************************************************************************/

Util::ModelManager *manager ()
{
        return Util::BajkaApp::instance ()->getManager ().get ();
}

/****************************************************************************/

namespace Util {
namespace M = Model;
namespace V = View;
namespace C = Controller;
namespace E = Event;

/**
 * pimpl
 */
struct Impl {

        Impl () : model (NULL), dropIteration_ (false) {}

        Ptr <BajkaConfig> config;
        Ptr <Event::DispatcherList> dispatchers;
        Ptr <ModelManager> manager;

        Model::IModel *model;
        ModelIndex listeners;

        bool dropIteration_;
        Event::UpdateEvent updateEvent;
};

BajkaApp *BajkaApp::instance_ = NULL;

/****************************************************************************/

BajkaApp::BajkaApp () : impl (new Impl) {}
BajkaApp::~BajkaApp () { delete impl; }

/****************************************************************************/

BajkaApp *BajkaApp::instance ()
{
        assertThrow (instance_, "!instance_")
        return instance_;
}

/****************************************************************************/

void BajkaApp::init ()
{
#if 1

        /* Initialize SDL for video output */
        if (SDL_Init (SDL_INIT_VIDEO) < 0) {
                fprintf (stderr, "Unable to initialize SDL: %s\n", SDL_GetError ());
                exit (1);
        }

        int flags;
        if (::config ()->getFullScreen ()) {
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

        int resX = ::config ()->getResX ();
        int resY = ::config ()->getResY ();

        /* Create a OpenGL screen */
        if (SDL_SetVideoMode (resX, resY, 0, flags) == NULL) {
                fprintf (stderr, "Unable to create OpenGL screen: %s\n", SDL_GetError ());
                SDL_Quit ();
                exit (2);
        }

        /* Set the title bar in environments that support it */
        SDL_WM_SetCaption (::config ()->getWindowCaption ().c_str (), NULL);

/*##########################################################################*/

        if (TTF_Init () < 0) {
            throw InitException ("TTF_Init failed");
        }

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

/*##########################################################################*/

        // Transformacje.
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        // gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
        gluOrtho2D (-resX/2, resX/2, -resY/2, resY/2);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluOrtho2D (-resX/2, resX/2, -resY/2, resY/2);
//        glViewport (0, 0, (GLsizei) resX, (GLsizei) resY);

        GLfloat params[100];
        glGetFloatv (GL_ALIASED_POINT_SIZE_RANGE, params);
        std::cerr << "GL_ALIASED_POINT_SIZE_RANGE : " << params[0] << ", " << params[1] << std::endl;

        glGetFloatv (GL_SMOOTH_POINT_SIZE_RANGE, params);
        std::cerr << "GL_SMOOTH_POINT_SIZE_RANGE : " << params[0] << ", " << params[1] << std::endl;

        glGetFloatv (GL_SMOOTH_POINT_SIZE_GRANULARITY, params);
        std::cerr << "GL_SMOOTH_POINT_SIZE_GRANULARITY : " << params[0] << ", " << params[1] << std::endl;

//        glEnable(GL_LINE_SMOOTH);
//        glEnable(GL_POINT_SMOOTH);
//        glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
//        glHint(GL_POINT_SMOOTH_HINT, GL_DONT_CARE);

        std::cerr << "is enabled GL_POINT_SMOOTH : " << ((glIsEnabled (GL_POINT_SMOOTH)) ? ("true") : ("false")) << std::endl;

        glPointSize (3);
        glGetFloatv (GL_POINT_SIZE, params);
        std::cerr << "GL_POINT_SIZE : " << params[0] << std::endl;

        // glDrawArrays
        glEnableClientState(GL_VERTEX_ARRAY);

        // Init rand
        srand (time (NULL));

        Tween::init ();

        SDL_ShowCursor (impl->config->getShowSystemCursor ());

#endif
#if 0
        if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            return ;
        }

        SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);

        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          16);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,            32);

        SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,        8);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,        8);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);

        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

        if((/*Surf_Display = */SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) {
            return;
        }

        glClearColor(0, 0, 0, 0);

        glViewport(0, 0, 640, 480);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glOrtho(0, 640, 480, 0, 1, -1);

        glMatrixMode(GL_MODELVIEW);

        glEnable(GL_TEXTURE_2D);

        glLoadIdentity();

        return;
#endif
}

/****************************************************************************/
#define checkBreak() { if (impl->dropIteration_) { break; } }
#define checkContinue() { if (impl->dropIteration_) { continue; } }

void BajkaApp::loop ()
{
        bool done = false;

        if (!impl->model) {
        	throw InitException ("BajkaApp has no model.");
        }

        Uint32 lastMs = SDL_GetTicks ();

        while (!done) {

                impl->dropIteration_ = false;
                Uint32 currentMs = SDL_GetTicks ();
                int deltaMs = currentMs - lastMs;
                lastMs = currentMs;

                glMatrixMode (GL_MODELVIEW);
                glLoadIdentity ();
                glClearColor (0.35, 0.75, 1.0, 1.0);
                glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                // Run models, views and controllers.
                // Generuj eventy.
                for (Event::DispatcherList::const_iterator i = impl->dispatchers->begin (); i != impl->dispatchers->end (); i++) {
                        (*i)->run (impl->model, impl->listeners);
                        checkBreak ();
                }

                checkContinue ();
                impl->updateEvent.setDeltaMs (deltaMs);
                impl->model->update (&impl->updateEvent);
                checkContinue ();

                // Run chipmunk
                if (Model::Space::getSpace ()) {
                        cpSpaceStep (Model::Space::getSpace (), 1.0 / 60.0);
                }

                Tween::Manager::getMain ()->update (deltaMs);
                checkContinue ();

                glFlush ();
                // swap buffers to display, since we're double buffered.
                SDL_GL_SwapBuffers ();
                // Tak śmiga, że damy delay
                SDL_Delay (5);
        }
}

/****************************************************************************/

void BajkaApp::debug (Core::String const &msg)
{
        std::cerr << "+---------------DEBUG-------[" << msg << "]--------+" << std::endl;
}

/****************************************************************************/

void BajkaApp::destroy ()
{
        TTF_Quit ();
        SDL_Quit ();
	Tween::free ();

        std::cerr << "+---------------QUIT----------------+" << std::endl;
        std::cerr << "gl version : " << glGetString(GL_VERSION) << std::endl;

        int i;
        glGetIntegerv (GL_MAX_TEXTURE_SIZE, &i);
        std::cerr << "max texture size : " << i << std::endl;
}

/****************************************************************************/

Ptr <BajkaConfig> BajkaApp::getConfig () const
{
        return impl->config;
}

/****************************************************************************/

void BajkaApp::setConfig (Ptr <BajkaConfig> b)
{
        impl->config = b;
}

/****************************************************************************/

Model::IModel *BajkaApp::getModel () const
{
        return impl->model;
}

/****************************************************************************/

void BajkaApp::setModel (Model::IModel *m)
{
        impl->model = m;
        impl->listeners.clear ();
        reindex (0xFFFFu & ~(Event::MOUSE_MOTION_EVENT | Event::BUTTON_PRESS_EVENT | Event::BUTTON_RELEASE_EVENT), m);
}

/****************************************************************************/

Ptr <ModelManager> BajkaApp::getManager ()
{
        return impl->manager;
}

/****************************************************************************/

void BajkaApp::setManager (Ptr <ModelManager> m)
{
        impl->manager = m;
        impl->manager->setApp (this);
}

/****************************************************************************/

unsigned int BajkaApp::reindex (unsigned int eventMask, Model::IModel *m)
{
        /*
         * Wszystkie eventy na które reagują moje dzieci - ja już nie muszę na nie reagować,
         * bo eventy idą od dziecka do rodzica i wówczas jest jeszcze jedno sprawdzenie
         */
        unsigned int childMask = 0x0;

        if (m->isGroup ()) {
                M::IGroup *g = dynamic_cast <M::IGroup *> (m);

                for (Model::ModelVector::const_iterator i = g->getChildren ().begin ();
                         i != g->getChildren ().end ();
                         ++i) {

                                childMask |= reindex (eventMask, *i);
                }
        }

        unsigned int eventsToRun = 0x0;

        if (m->getController ()) {
                eventsToRun = m->getController ()->getEventMask ();

                if (!eventsToRun) {
                        return 0;
                }

                eventsToRun &= ~(eventsToRun & childMask);
                childMask = eventsToRun; // Zmienna uzyta ponownie, ale w innym celu.

                for (unsigned int i = 1; i != Event::EVENT_TERMINATOR; i <<= 1) {

                        if (m->getController ()->getEventMask () & i) {
                                impl->listeners.insert (std::make_pair ((Event::Type)i, m));
                                childMask &= ~i;
                        }
                }

                return childMask;
        }

        return eventsToRun;
}

/****************************************************************************/

Ptr <Event::DispatcherList> BajkaApp::getDispatchers () const
{
        return impl->dispatchers;
}

/****************************************************************************/

void BajkaApp::setDispatchers (Ptr <Event::DispatcherList> d)
{
        impl->dispatchers = d;

        for (Event::DispatcherList::const_iterator i = impl->dispatchers->begin (); i != impl->dispatchers->end (); i++) {
                (*i)->setApp (this);
        }
}

/****************************************************************************/

void BajkaApp::reset ()
{
        dropIteration ();

        impl->listeners.clear ();

        for (Event::DispatcherList::const_iterator i = impl->dispatchers->begin (); i != impl->dispatchers->end (); i++) {
                (*i)->reset ();
        }
}

/****************************************************************************/

void BajkaApp::dropIteration ()
{
        impl->dropIteration_ = true;
}

/****************************************************************************/

bool BajkaApp::getDropIteration () const
{
        return impl->dropIteration_;
}

} // Nam
