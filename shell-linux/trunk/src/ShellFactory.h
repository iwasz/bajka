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

class GameLoop;
class ShellContext;
class LifecycleHandler;
class GraphicsService;

namespace Sound {
class IDevice;
}

namespace Util {
class ShellConfig;
class BajkaService;
}

/**
 *
 */
class ShellFactory {
public:

        static std::auto_ptr <GameLoop> createGameLoop (Util::ShellConfig *sConfig);

private:

        /// Usunać za pomocą delete
        static ShellContext *createShellContext (Util::ShellConfig *sConfig);
        static LifecycleHandler *createLifecycleHandler ();
        static GraphicsService *createGraphicsService ();
        static Util::BajkaService *createBajkaService ();

};

#endif /* SHELLFACTORY_H_ */
