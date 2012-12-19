/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Buffer.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <sound/SoundException.h>
#include <util/Exceptions.h>
#include <android/asset_manager.h>
#include <android_native_app_glue.h>

/****************************************************************************/

struct Buffer::Impl {

        Impl () : fdPlayerObject (NULL), fdPlayerPlay (NULL), fdPlayerSeek (NULL), fdPlayerMuteSolo (NULL), fdPlayerVolume (NULL) {};

        std::string name;
        SLObjectItf fdPlayerObject;
        SLPlayItf fdPlayerPlay;
        SLSeekItf fdPlayerSeek;
        SLMuteSoloItf fdPlayerMuteSolo;
        SLVolumeItf fdPlayerVolume;
};

/****************************************************************************/

Buffer::Buffer ()
{
        impl = new Impl;
}

/****************************************************************************/

Buffer::~Buffer ()
{
        delete impl;
}

/****************************************************************************/

void Buffer::setLoad (std::string const &path)
{
        SLresult result;
        assert (impl->app->activity->assetManager);
        AAsset* asset = AAssetManager_open (impl->app->activity->assetManager, filename.c_str (), AASSET_MODE_UNKNOWN);

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
        SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, impl->outputMixObject };
        SLDataSink audioSnk = { &loc_outmix, NULL };

        // create audio player
        const SLInterfaceID ids[3] = { SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME };
        const SLboolean req[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

        result = (*impl->engineEngine)->CreateAudioPlayer (impl->engineEngine, &fdPlayerObject, &audioSrc, &audioSnk, 3, ids, req);
        assert(SL_RESULT_SUCCESS == result);

        // realize the player
        result = (*fdPlayerObject)->Realize(fdPlayerObject, SL_BOOLEAN_FALSE);
        assert(SL_RESULT_SUCCESS == result);

        // get the play interface
        result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_PLAY, &fdPlayerPlay);
        assert(SL_RESULT_SUCCESS == result);

        // get the seek interface
        result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_SEEK, &fdPlayerSeek);
        assert(SL_RESULT_SUCCESS == result);

        // get the mute/solo interface
        result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_MUTESOLO, &fdPlayerMuteSolo);
        assert(SL_RESULT_SUCCESS == result);

        // get the volume interface
        result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_VOLUME, &fdPlayerVolume);
        assert(SL_RESULT_SUCCESS == result);

        // enable whole file looping
        result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
        assert(SL_RESULT_SUCCESS == result);

        // Uruchomienie zapętlonego dźwięku z Asseta
        // set the player's state
//        result = (*fdPlayerPlay)->SetPlayState (fdPlayerPlay, isPlaying ? SL_PLAYSTATE_PLAYING : SL_PLAYSTATE_PAUSED);
        result = (*fdPlayerPlay)->SetPlayState (fdPlayerPlay, SL_PLAYSTATE_PLAYING);
        assert(SL_RESULT_SUCCESS == result);
}

/****************************************************************************/

void Buffer::setName (std::string const &name)
{
        impl->name = name;
//        assertThrow (device, "Buffer::setName : device must be set prior to calling this method.");
//        device->unregisterBuffer (name);
//        device->registerBuffer (name, this);
}

/****************************************************************************/

std::string const &Buffer::getName () const
{
        return impl->name;
}

/****************************************************************************/

unsigned int Buffer::getSystemId () const
{
//        return impl->buffer;
        return 0;
}
