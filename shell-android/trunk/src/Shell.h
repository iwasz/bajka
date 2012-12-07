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

struct android_app;
struct AInputEvent;
extern int32_t handleInput (struct android_app *app, AInputEvent *event);
extern void handleCmdInit (struct android_app* app, int32_t cmd);

/**
 *
 */
class Shell : public Util::AbstractShell {
public:

        virtual ~Shell ();
        static Shell *instance () { return &instance_; }

        Common::DataSource *newDataSource ();
        void deleteDataSource (Common::DataSource *ds);

        Event::IEventDispather *getEventDispatcher ();

private:

        Shell ();

        void initDependent ();
        void destroy ();
        void swapBuffers ();
        void initDisplay ();

        friend Util::IShell *shell ();
        friend int32_t handleInput (struct android_app* app, AInputEvent *event);
        friend void handleCmdInit (struct android_app* app, int32_t cmd);

private:

        static Shell instance_;
        struct Impl;
        Impl *myimpl;

};

#endif /* SHELL_H_ */
