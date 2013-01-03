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
extern int printlogImpl (const char *format, ...);

#ifndef NDEBUG
#define printlog(...) printlogImpl(__VA_ARGS__)
#else
#define printlog(...)
#endif

namespace Common {
class DataSource;
}

extern Common::DataSource *newDataSource ();
extern void deleteDataSource (Common::DataSource *ds);

namespace Util {
class Config;
}

namespace View {
class GLContext;
}

extern Util::Config *config ();
extern void quit ();

#endif /* SHELL_H_ */
