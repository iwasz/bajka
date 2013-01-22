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
class GraphicsService;
class EventDispatcher;

namespace Sound {
class IDevice;
}

namespace Util {
class ShellConfig;
class BajkaService;
class ShellContext;
class LifecycleHandler;
}

/**
 *
 */
class ShellFactory {
public:

        static std::auto_ptr <GameLoop> createGameLoop (Util::ShellConfig *sConfig);

private:

        /// Usunać za pomocą delete
        static Util::ShellContext *createShellContext (Util::ShellConfig *sConfig);
        static Util::LifecycleHandler *createLifecycleHandler ();
        static GraphicsService *createGraphicsService ();
        static Util::BajkaService *createBajkaService ();
        static EventDispatcher *createEventDispatcher ();

private:

        static Core::VariantMap singletons;
};

#endif /* SHELLFACTORY_H_ */
