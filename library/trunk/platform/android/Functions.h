/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@tiliae.eu                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifdef ANDROID
#ifndef PLATFORM_ANDROID_BAJKA_FUNCTIONS_H_
#define PLATFORM_ANDROID_BAJKA_FUNCTIONS_H_

#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "bajka", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "bajka", __VA_ARGS__))

#endif /* FUNCTIONS_H_ */
#endif
