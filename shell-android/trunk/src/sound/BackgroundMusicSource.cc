/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "BackgroundMusicSource.h"
#include "SoundContext.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <sound/SoundException.h>
#include <util/Exceptions.h>
#include <android/asset_manager.h>
#include <android_native_app_glue.h>
#include "Utils.h"

/****************************************************************************/

struct BackgroundMusicSource::Impl {

        Impl () : fdPlayerObject (NULL), fdPlayerPlay (NULL), fdPlayerSeek (NULL), fdPlayerMuteSolo (NULL), fdPlayerVolume (NULL) {};

        std::string name;
        SLObjectItf fdPlayerObject;
        SLPlayItf fdPlayerPlay;
        SLSeekItf fdPlayerSeek;
        SLMuteSoloItf fdPlayerMuteSolo;
        SLVolumeItf fdPlayerVolume;
};

/****************************************************************************/

BackgroundMusicSource::BackgroundMusicSource ()
{
        impl = new Impl;
}

/****************************************************************************/

BackgroundMusicSource::~BackgroundMusicSource ()
{
        // destroy file descriptor audio player object, and invalidate all associated interfaces
        if (impl->fdPlayerObject != NULL) {
                (*impl->fdPlayerObject)->Destroy (impl->fdPlayerObject);
                impl->fdPlayerObject = NULL;
                impl->fdPlayerPlay = NULL;
                impl->fdPlayerSeek = NULL;
                impl->fdPlayerMuteSolo = NULL;
                impl->fdPlayerVolume = NULL;
        }

        delete impl;
}

/****************************************************************************/

void BackgroundMusicSource::setLoad (std::string const &filename)
{
        assert (device);
        SoundContext *ctx = device->getSoundContext ();
        SLresult result;
        assert (ctx->app->activity->assetManager);
        AAsset* asset = AAssetManager_open (ctx->app->activity->assetManager, filename.c_str (), AASSET_MODE_UNKNOWN);
        assert (asset);

        // open asset as file descriptor
        off_t start, length;
        int fd = AAsset_openFileDescriptor(asset, &start, &length);
        assert(0 <= fd);
        AAsset_close(asset);

        // configure audio source
        SLDataLocator_AndroidFD loc_fd = { SL_DATALOCATOR_ANDROIDFD, fd, start, length };
        SLDataFormat_MIME format_mime = { SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED };
        SLDataSource audioSrc = { &loc_fd, &format_mime };

        // configure audio sink
        SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, ctx->outputMixObject };
        SLDataSink audioSnk = { &loc_outmix, NULL };

        // create audio player
        const SLInterfaceID ids[3] = { SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME };
        const SLboolean req[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

        result = (*ctx->engineEngine)->CreateAudioPlayer (ctx->engineEngine, &impl->fdPlayerObject, &audioSrc, &audioSnk, 3, ids, req);
        assert(SL_RESULT_SUCCESS == result);
        soundThrow (result);

        // realize the player
        result = (*impl->fdPlayerObject)->Realize (impl->fdPlayerObject, SL_BOOLEAN_FALSE);
        soundThrow (result);

        // get the play interface
        result = (*impl->fdPlayerObject)->GetInterface (impl->fdPlayerObject, SL_IID_PLAY, &impl->fdPlayerPlay);
        soundThrow (result);

        // get the seek interface
        result = (*impl->fdPlayerObject)->GetInterface (impl->fdPlayerObject, SL_IID_SEEK, &impl->fdPlayerSeek);
        soundThrow (result);

        // get the mute/solo interface
        result = (*impl->fdPlayerObject)->GetInterface (impl->fdPlayerObject, SL_IID_MUTESOLO, &impl->fdPlayerMuteSolo);
        soundThrow (result);

        // get the volume interface
        result = (*impl->fdPlayerObject)->GetInterface (impl->fdPlayerObject, SL_IID_VOLUME, &impl->fdPlayerVolume);
        soundThrow (result);

        // enable whole file looping
        result = (*impl->fdPlayerSeek)->SetLoop (impl->fdPlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
        soundThrow (result);

        // Uruchomienie zapętlonego dźwięku z Asseta
        // set the player's state
//        result = (*fdPlayerPlay)->SetPlayState (fdPlayerPlay, isPlaying ? SL_PLAYSTATE_PLAYING : SL_PLAYSTATE_PAUSED);
//        result = (*impl->fdPlayerPlay)->SetPlayState (impl->fdPlayerPlay, SL_PLAYSTATE_PLAYING);
//        soundThrow (result);
}

/****************************************************************************/

void BackgroundMusicSource::setName (std::string const &name)
{
        impl->name = name;
//        assertThrow (device, "BackgroundMusicSource::setName : device must be set prior to calling this method.");
//        device->unregisterBuffer (name);
//        device->registerBuffer (name, this);
}

/****************************************************************************/

std::string const &BackgroundMusicSource::getName () const
{
        return impl->name;
}

