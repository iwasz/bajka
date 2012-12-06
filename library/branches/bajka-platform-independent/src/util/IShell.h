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

namespace Common {
class DataSource;
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
                loopDelayMs (-1),
                definitionFile ("main.xml"),
                configFile ("config.xml") {}

        bool            fullScreen;
        int             viewportWidth;
        int             viewportHeight;
        bool            showAABB;
        int             loopDelayMs;
        std::string     definitionFile;
        std::string     configFile;
};

/**
 * Abstrakcja bebechów TODO napisać coś mądrego.
 */
class IShell {
public:
        virtual ~IShell() {}

        virtual int run (Util::ShellConfig const &cfg, void *userData) = 0;
        virtual void quit () = 0;

        virtual Util::Config *getConfig () = 0;
        virtual View::GLContext *getGLContext () = 0;

        virtual void onManagerLoadModel () = 0;
        virtual void onManagerUnloadModel () = 0;

        virtual void setModel (Model::IModel *model) = 0;

        /**
         * Must be freed after use. Those metods (new and delete) are
         * parts of IShell API, because of dependencies needed during creation
         * of DataSource itself. Under Android AAssetManager is necessary
         * for this, and is stored in IShell class.
         */
        virtual Common::DataSource *newDataSource () = 0;
        virtual void deleteDataSource (Common::DataSource *ds) = 0;

protected:

        virtual void prepare (void *userData) = 0;
        virtual void readConfig (Common::DataSource *ds, Util::ShellConfig const &cfg) = 0;
        virtual void overrideConfig (Util::ShellConfig const &cfg) = 0;
        virtual void initIndependent () = 0;
        virtual void initDependent () = 0;
        virtual void readDefinition (Common::DataSource *ds, Util::ShellConfig const &cfg) = 0;

        virtual void loop () = 0;
        virtual void destroy () = 0;
        virtual void swapBuffers () = 0;

};

} /* namespace Util */
#endif /* ISHELL_H_ */
