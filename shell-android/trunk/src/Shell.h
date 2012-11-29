/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_H_
#define BAJKA_SHELL_H_

#include <util/AbstractShell.h>

class Impl;

namespace Model {
class IModel;
}

/**
 *
 */
class Shell : public Util::AbstractShell {
public:

        virtual ~Shell ();
        static Shell *instance () { return &instance_; }
        void reset ();

private:

        Shell ();

        void init ();
        void preInit ();
        void destroy ();
        void dispatchEvents ();
        void swapBuffers ();
        Common::DataSource *newDataSource ();

        friend Util::IShell *shell ();

private:

        static Shell instance_;
        struct Impl;
        Impl *myimpl;

};

#endif /* SHELL_H_ */
