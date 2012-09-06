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

// Graphics
extern void swapBuffers ();

// Logging
extern int log (const char *format, ...);

#endif /* SHELL_H_ */
