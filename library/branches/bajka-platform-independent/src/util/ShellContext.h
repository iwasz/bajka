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

namespace View {
class GLContext;
}

namespace Util {
class ShellConfig;
class Config;

/**
 * DTO grubaśne.
 */
struct ShellContext {

        ShellContext ();

        Util::ShellConfig *shellConfig;
        Util::Config *config;
        View::GLContext *glContext;

};

}

#endif /* SHELLCONTEXT_H_ */
