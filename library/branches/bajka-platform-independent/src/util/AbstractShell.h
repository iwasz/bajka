/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_UTIL_ABSTRACTSHELL_H_
#define BAJKA_UTIL_ABSTRACTSHELL_H_

#include "IShell.h"

namespace Model {
class IModel;
}

namespace Util {
class AbstractShellImpl;
class Config;

/**
 * Wspólna implementacja dla szeli dla różnych systemów.
 */
class AbstractShell : public IShell {
public:
        AbstractShell ();
        virtual ~AbstractShell ();

        int run (Util::ShellConfig const &cfg, void *userData = NULL);
        void quit ();
        virtual void reset ();

        Model::IModel *getModel ();
        virtual void setModel (Model::IModel *model);

        Util::Config *getConfig ();
        View::GLContext *getGLContext ();

        void onManagerLoadModel ();
        void onManagerUnloadModel ();

protected:

        void loop ();
        virtual void destroy ();

        class Impl;
        AbstractShellImpl *impl;

private:

        void prepare (void *userData);
        void readConfig (Common::DataSource *ds, Util::ShellConfig const &cfg);
        void overrideConfig (Util::ShellConfig const &cfg);
        void initIndependent ();
        void readDefinition (Common::DataSource *ds, Util::ShellConfig const &cfg);

        void updateLayout (Model::IModel *root);

};

} /* namespace Util */

#endif /* ABSTRACTSHELL_H_ */
