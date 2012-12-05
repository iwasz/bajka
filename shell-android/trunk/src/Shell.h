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

        // TODO private
        void initDisplay ();

        Common::DataSource *newDataSource ();
        void deleteDataSource (Common::DataSource *ds);

private:

        Shell ();

        void init ();
        void destroy ();
        void dispatchEvents ();
        void swapBuffers ();

        friend Util::IShell *shell ();

private:

        static Shell instance_;
        struct Impl;
        Impl *myimpl;

};

#endif /* SHELL_H_ */
