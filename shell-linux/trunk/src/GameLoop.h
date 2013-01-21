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

private:

        ShellContext *context;
        LifecycleHandler *lifecycleHandler;
        bool autoPause;
        bool suspended;
//        bool firstInitWindow;
        bool firstGainedFocus;
        bool savedStatePending;
        bool rendering; // rendering i suspended są osobno, bo w czasie inicjowania mają odwrotne wartości.
};

#endif /* GAMELOOP_H_ */
