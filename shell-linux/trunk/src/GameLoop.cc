/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Platform.h>
#include "GameLoop.h"
#include <util/ShellContext.h>
#include <util/LifecycleHandler.h>
#include <core/Exception.h>
#include <exception>
#include <cstdlib>
#include <SDL.h>

/****************************************************************************/

GameLoop::GameLoop (Util::ShellContext *c, Util::LifecycleHandler *h) :
        context (c),
        lifecycleHandler (h),
        autoPause (false),
        suspended (false),
        firstGainedFocus (true),
        savedStatePending (false),
        rendering (false)
{
}

/****************************************************************************/

GameLoop::~GameLoop ()
{
        delete context;
        delete lifecycleHandler;
}

/****************************************************************************/

void GameLoop::init ()
{
        lifecycleHandler->onFirstTimeReadyForRender (context);
        rendering = true;
}

/****************************************************************************/

void GameLoop::loop ()
{
        try {
                uint32_t lastMs = getCurrentMs ();
                uint32_t deltaMs = 0;

                while (true) {

                        if (rendering) {
                                lifecycleHandler->onStep (context, autoPause, deltaMs);
                        }

                        // Tu eventy pobierz
                        SDL_Event event;
                        bool handled = false;

                        while (SDL_PollEvent (&event)) {

                                if (rendering) {
                                        /*
                                         * onInputEvent zwróci true, jesli bajka w jakikolwiek zareagowała na event.
                                         * False, jeśli nie zareagowała i wówczas event trafi do systemu i zostanie
                                         * obsłużony w domyślny sposób.
                                         */
                                        handled = lifecycleHandler->onInputEvent (context, &event);
                                }

                                if (!handled) {
                                        switch (event.type) {
                                        case SDL_ACTIVEEVENT:
                                                if (event.active.state == SDL_APPMOUSEFOCUS) {
                                                        break;
                                                }

                                                if (event.active.gain) {
                                                        lifecycleHandler->onGainedFocus (context, false);
                                                }
                                                else {
                                                        lifecycleHandler->onLostFocus (context);
                                                }

                                                continue;

                                        case SDL_QUIT:
                                                lifecycleHandler->onStop (context);
                                                return;

                                        default:
                                                break;
                                        }
                                }
                        }
                }
        }
        catch (Core::Exception const &e) {
                printlog ("GameLoop::loop : Core::Exception caught : %s\n", e.getMessage ().c_str ());
                abort ();
        }
        catch (std::exception const &e) {
                printlog ("GameLoop::loop : std::exception caught : %s\n", e.what ());
                abort ();
        }
        catch (...) {
                printlog ("GameLoop::loop : Unknown exception caught");
                abort ();
        }
}

