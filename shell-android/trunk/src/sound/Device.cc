/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Device.h"
#include "SoundContext.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <cstddef>
#include <android/asset_manager.h>
#include <android_native_app_glue.h>
#include <Platform.h>

// TODO wywal
#include <cassert>

/**
 *
 */
struct Device::Impl {
        Impl () : app (NULL),
                  engineObject (NULL),
                  engineEngine (NULL),
                  outputMixObject (NULL),
                  outputMixEnvironmentalReverb (NULL) {}

        android_app *app;
        // engine interfaces
        SLObjectItf engineObject;
        SLEngineItf engineEngine;

        // output mix interfaces
        SLObjectItf outputMixObject;
        SLEnvironmentalReverbItf outputMixEnvironmentalReverb;
        SoundContext context;
};

/****************************************************************************/

Device::Device () : impl (new Impl)
{
}

/****************************************************************************/

Device::~Device ()
{
        // destroy engine object, and invalidate all associated interfaces
        if (impl->engineObject != NULL) {
                (*impl->engineObject)->Destroy(impl->engineObject);
                impl->engineObject = NULL;
                impl->engineEngine = NULL;
        }

        delete impl;
}

/****************************************************************************/

void Device::init (void *systemData)
{
        impl->app = static_cast <android_app *> (systemData);
        SLresult result;

        // create engine
        result = slCreateEngine (&impl->engineObject, 0, NULL, 0, NULL, NULL);
        assert(SL_RESULT_SUCCESS == result);

        // realize the engine
        result = (*impl->engineObject)->Realize (impl->engineObject, SL_BOOLEAN_FALSE);
        assert(SL_RESULT_SUCCESS == result);

        // get the engine interface, which is needed in order to create other objects
        result = (*impl->engineObject)->GetInterface (impl->engineObject, SL_IID_ENGINE, &impl->engineEngine);
        assert(SL_RESULT_SUCCESS == result);

        // create output mix, with environmental reverb specified as a non-required interface
        const SLInterfaceID ids[1] = { SL_IID_ENVIRONMENTALREVERB };
        const SLboolean req[1] = { SL_BOOLEAN_FALSE };
        result = (*impl->engineEngine)->CreateOutputMix (impl->engineEngine,  &impl->outputMixObject, 1, ids, req);
        assert(SL_RESULT_SUCCESS == result);

        // realize the output mix
        result = (*impl->outputMixObject)->Realize (impl->outputMixObject, SL_BOOLEAN_FALSE);
        assert(SL_RESULT_SUCCESS == result);

        // get the environmental reverb interface
        // this could fail if the environmental reverb effect is not available,
        // either because the feature is not present, excessive CPU load, or
        // the required MODIFY_AUDIO_SETTINGS permission was not requested and granted
        result = (*impl->outputMixObject)->GetInterface (impl->outputMixObject, SL_IID_ENVIRONMENTALREVERB, &impl->outputMixEnvironmentalReverb);

        if (SL_RESULT_SUCCESS == result) {
                // aux effect on the output mix, used by the buffer queue player TODO Nie mam pojęcia, czy ta zmienna musi istnieć po wyjściu z tego zakresu, czy nie, dlatego daję static.
                static const SLEnvironmentalReverbSettings reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;
                result = (*impl->outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties (impl->outputMixEnvironmentalReverb, &reverbSettings);
        }
        // ignore unsuccessful result codes for environmental reverb, as it is optional for this example

        impl->context.app = impl->app;
        impl->context.engineEngine = impl->engineEngine;
        impl->context.outputMixObject = impl->outputMixObject;
}

/****************************************************************************/

void Device::printInfo ()
{
        printlog ("Device::printInfo here");
}

/****************************************************************************/

SoundContext *Device::getSoundContext ()
{
        return &impl->context;

}
