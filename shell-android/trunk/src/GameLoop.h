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
class ShellFactory;

/**
 *
 */
class GameLoop {
public:

        ~GameLoop ();

        void init ();
        void loop ();

private:

        friend class ShellFactory;
        GameLoop (ShellContext *c, LifecycleHandler *h);

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
        bool firstInitWindow;
        bool firstGainedFocus;
        bool savedStatePending;
        bool rendering;
};

#endif /* GAMELOOP_H_ */
