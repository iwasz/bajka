/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SHELLFACTORY_H_
#define SHELLFACTORY_H_

#include <memory>
#include <core/Typedefs.h>

class GameLoop;
struct android_app;
class GraphicsService;
class EventDispatcher;

namespace Sound {
class IDevice;
}

namespace Util {
class LifecycleHandler;
class ShellConfig;
class BajkaService;
class ShellContext;
}

/**
 *
 */
class ShellFactory {
public:

        static std::auto_ptr <GameLoop> createGameLoop (Util::ShellConfig *sConfig, android_app *app);

private:

        /// Usunać za pomocą delete
        static Util::ShellContext *createShellContext (Util::ShellConfig *sConfig, android_app *app);
        static Util::LifecycleHandler *createLifecycleHandler ();
        static GraphicsService *createGraphicsService (android_app *app);
        static Util::BajkaService *createBajkaService ();
        static EventDispatcher *createEventDispatcher ();

private:

        static Core::VariantMap singletons;

};

#endif /* SHELLFACTORY_H_ */
