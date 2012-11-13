/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_ISHELL_H_
#define BAJKA_ISHELL_H_

#include <string>

namespace View {
class GLContext;
}

namespace Model {
class IModel;
}

namespace Util {
class Config;

/**
 * Config.
 */
struct ShellConfig {

        ShellConfig () :
                fullScreen (false),
                viewportWidth (-1),
                viewportHeight (-1),
                showAABB (false),
                loopDelayMs (-1) {}

        bool             fullScreen;
        int             viewportWidth;
        int             viewportHeight;
        bool             showAABB;
        int             loopDelayMs;
        std::string     definitionFile;
};

/**
 * Abstrakcja bebechów TODO napisać coś mądrego.
 */
class IShell {
public:
        virtual ~IShell() {}

        virtual int run (Util::ShellConfig const &cfg) = 0;
        virtual void quit () = 0;

        virtual void init () = 0;
        virtual void preInit () = 0;
        virtual void loop () = 0;
        virtual void destroy () = 0;

        virtual void onManagerLoadModel () = 0;
        virtual void onManagerUnloadModel () = 0;

        virtual void setModel (Model::IModel *model) = 0;
        virtual Util::Config *getConfig () = 0;
        virtual View::GLContext *getGLContext () = 0;

};

} /* namespace Util */
#endif /* ISHELL_H_ */
