/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef LINUX
#ifndef PLATFORM_LINUX_BAJKA_FUNCTIONS_H_
#define PLATFORM_LINUX_BAJKA_FUNCTIONS_H_

#include <cstdio>

#define LOGI(fromat, ...) ((void)vprintf (format, __VA_ARGS__))
#define LOGW LOGI

#endif /* FUNCTIONS_H_ */
#endif
