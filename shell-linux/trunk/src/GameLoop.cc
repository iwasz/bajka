/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Platform.h>
#include "GameLoop.h"
#include "ShellContext.h"
#include "LifecycleHandler.h"
#include <core/Exception.h>
#include <exception>
#include <cstdlib>

/****************************************************************************/

GameLoop::GameLoop (ShellContext *c, LifecycleHandler *h) :
        context (c),
        lifecycleHandler (h),
        autoPause (false),
        suspended (false),
        /*firstInitWindow (true),*/
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

                        // Tu eventy pobierz

                        if (rendering) {
                                lifecycleHandler->onStep (context, autoPause, deltaMs);
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

/****************************************************************************/

void GameLoop::handleCmd (android_app *app, int32_t cmd) {
        try {
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

/****************************************************************************/

int32_t GameLoop::handleInput (struct android_app* app, AInputEvent *event) {
}

/****************************************************************************/

void GameLoop::handleCmd (int32_t cmd)
{

}

/****************************************************************************/

int32_t GameLoop::handleInput (AInputEvent *event)
{
        if (rendering) {
                /*
                 * onInputEvent zwróci true, jesli bajka w jakikolwiek zareagowała na event.
                 * False, jeśli nie zareagowała i wówczas event trafi do systemu i zostanie
                 * obsłużony w domyślny sposób.
                 */
                return (int32_t)lifecycleHandler->onInputEvent (context, event);
        }

        return 0;
}
