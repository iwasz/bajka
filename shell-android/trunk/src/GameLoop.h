/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_GAMELOOP_H_
#define BAJKA_SHELL_GAMELOOP_H_

#include <stdint.h>

class ShellContext;
struct android_app;
struct AInputEvent;
class LifecycleHandler;

/**
 *
 */
class GameLoop {
public:

        GameLoop (ShellContext *c, LifecycleHandler *h);
        ~GameLoop ();

        void init ();
        void loop ();

private:

        static void handleCmd (android_app *app, int32_t cmd);
        void handleCmd (int32_t cmd);
        static int32_t handleInput (android_app *app, AInputEvent *event);
        int32_t handleInput (AInputEvent *event);

private:

        ShellContext *context;
        LifecycleHandler *lifecycleHandler;
        bool userPause;
        bool autoPause;
        bool suspended;
        bool firstLoad;
        bool savedStatePending;
        bool rendering;
};

#endif /* GAMELOOP_H_ */
