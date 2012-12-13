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
struct android_app;
class LifecycleHandler;
class GraphicsService;
class DataSourceService;

namespace Util {
class ShellConfig;
class BajkaService;
}

/**
 *
 */
class ShellFactory {
public:

        static std::auto_ptr <GameLoop> createGameLoop (Util::ShellConfig *sConfig, android_app *app);

private:

        /// Usunać za pomocą delete
        static ShellContext *createShellContext (Util::ShellConfig *sConfig, android_app *app);
        static LifecycleHandler *createLifecycleHandler ();
        static GraphicsService *createGraphicsService (android_app *app);
        static Util::BajkaService *createBajkaService ();
        static DataSourceService *createDataSourceService (android_app *app);

};

#endif /* SHELLFACTORY_H_ */