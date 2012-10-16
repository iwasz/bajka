/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_H_
#define BAJKA_SHELL_H_

#include "util/IShell.h"
#include "./resource/Resource.h"

class Impl;

namespace Model {
class IModel;
}

/*
 * TODO Ta klasa ma wiele metod, ktore nie muszą być w shelu, tylko powinny być w kodzie wspólny, czyli w bajce.
 */
class Shell : public Util::IShell {
public:

        virtual ~Shell ();

        static Shell *instance () { return &instance_; }

        int run (Util::ShellConfig const &cfg);
        void quit ();

        void reset ();

        Model::IModel *getModel ();
        virtual void setModel (Model::IModel *model);

        Util::Config *getConfig ();

        void onManagerLoadModel ();
        void onManagerUnloadModel ();

private:

        Shell ();
        void init ();
        void loop ();
        void destroy ();
        void overrideConfig (Util::ShellConfig const &cfg);
        void updateLayout (Model::IModel *root);
        friend Util::IShell *shell ();

private:

        Impl *impl;
        static Shell instance_;

};

#endif /* SHELL_H_ */
