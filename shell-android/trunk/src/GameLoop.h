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

namespace Util {
class ShellContext;
class LifecycleHandler;
}

struct android_app;
struct AInputEvent;
class ShellFactory;
struct android_app;

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
        GameLoop (Util::ShellContext *c, Util::LifecycleHandler *h, android_app *a);

        static void handleCmd (android_app *app, int32_t cmd);
        void handleCmd (int32_t cmd);
        static int32_t handleInput (android_app *app, AInputEvent *event);
        int32_t handleInput (AInputEvent *event);

private:

        Util::ShellContext *context;
        Util::LifecycleHandler *lifecycleHandler;
        android_app *app;
        bool autoPause;
        bool suspended;
        bool firstInitWindow;
        bool firstGainedFocus;
        bool savedStatePending;
        bool rendering; // rendering i suspended są osobno, bo w czasie inicjowania mają odwrotne wartości.
};

#endif /* GAMELOOP_H_ */
