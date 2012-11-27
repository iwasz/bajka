/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SHELL_PLATFORM_H_
#define BAJKA_SHELL_PLATFORM_H_

#include <stdint.h>

// Time
extern uint32_t getCurrentMs ();
extern void delayMs (uint32_t);

// Logging
extern int printlog (const char *format, ...);

namespace Util {
class Config;
class IShell;
}

namespace View {
class GLContext;
}

extern Util::Config *config ();
extern Util::IShell *shell ();
extern View::GLContext *glContext ();

#endif /* SHELL_H_ */
