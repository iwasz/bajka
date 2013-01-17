/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SHELLCONTEXT_H_
#define SHELLCONTEXT_H_

class ShellFactory;

namespace Util {
class ShellConfig;
class Config;
}

namespace View {
class GLContext;
}

/**
 * DTO grubaśne.
 */
struct ShellContext {

        Util::ShellConfig *shellConfig;
        Util::Config *config;
        View::GLContext *glContext;

private:

        ShellContext ();
        ShellContext (ShellContext const &) {}
        friend class ShellFactory;

};

#endif /* SHELLCONTEXT_H_ */
