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

class Shell : public Util::IShell {
public:

        virtual ~Shell ();

        static Shell *instance () { return &instance_; }

        int run (Util::ShellConfig const &cfg);
        void quit ();

//        virtual void dropIteration ();
//        virtual bool getDropIteration () const;
        void reset ();

        Model::IModel *getModel ();
        virtual void setModel (Model::IModel *model);

        Util::Config *getConfig ();

        void notifyLoadModel ();
        void notifyUnloadModel ();

private:

        Shell ();
        void init ();
        void loop ();
        void destroy ();
        void overrideConfig (Util::ShellConfig const &cfg);
        friend Util::IShell *shell ();

private:

        Impl *impl;
        static Shell instance_;

};

#endif /* SHELL_H_ */
