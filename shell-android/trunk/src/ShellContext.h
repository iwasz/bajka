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

namespace Util {
class ShellConfig;
}

/**
 * DTO grubaśne.
 */
struct ShellContext {

        ShellContext ();

        Util::ShellConfig *shellConfig;
        android_app *app;

};

#endif /* SHELLCONTEXT_H_ */
