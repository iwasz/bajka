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

struct android_app;
struct AInputEvent;
class ShellFactory;

namespace Util {
class ShellContext;
class LifecycleHandler;
}

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
        GameLoop (Util::ShellContext *c, Util::LifecycleHandler *h);

private:

        Util::ShellContext *context;
        Util::LifecycleHandler *lifecycleHandler;
        bool autoPause;
        bool suspended;
        bool firstGainedFocus;
        bool savedStatePending;
        bool rendering; // rendering i suspended są osobno, bo w czasie inicjowania mają odwrotne wartości.
};

#endif /* GAMELOOP_H_ */
