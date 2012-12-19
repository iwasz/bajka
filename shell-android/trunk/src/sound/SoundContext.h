/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_SOUNDCONTEXT_H_
#define BAJKA_SOUNDCONTEXT_H_

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <android_native_app_glue.h>

/**
 * DTO. Private interface. Not for users.
 */
struct SoundContext {
        SoundContext () : app (NULL), engineEngine (NULL), outputMixObject (NULL) {}

        android_app *app;
        SLEngineItf engineEngine;
        SLObjectItf outputMixObject;
};

#endif /* SOUNDCONTEXT_H_ */
