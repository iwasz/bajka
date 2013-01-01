/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef SHELL_SOUND_UTILS_H_
#define SHELL_SOUND_UTILS_H_

#include <string>
#include <SLES/OpenSLES.h>

extern std::string slResultToString (SLresult result);
extern void soundThrowImpl (const char *file, long line, const char *function, SLresult result, std::string const &msg = "");

#ifndef NDEBUG
#define soundThrow(...) soundThrowImpl(__FILE__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__)
#else
#define soundThrow(...)
#endif


#endif /* UTILS_H_ */
