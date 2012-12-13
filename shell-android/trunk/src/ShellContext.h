/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SHELLCONTEXT_H_
#define SHELLCONTEXT_H_

struct android_app;
class ShellFactory;

namespace Util {
class ShellConfig;
class Config;
}

/**
 * DTO grubaśne.
 */
struct ShellContext {

        Util::ShellConfig *shellConfig;
        Util::Config *config;
        android_app *app;

private:

        ShellContext ();
        ShellContext (ShellContext const &) {}
        friend class ShellFactory;

};

#endif /* SHELLCONTEXT_H_ */