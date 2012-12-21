/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Buffer.h"
#include "SoundContext.h"
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <sound/SoundException.h>
#include <util/Exceptions.h>
#include <android/asset_manager.h>
#include <android_native_app_glue.h>
#include <stdint.h>

/****************************************************************************/

struct Buffer::Impl {

        Impl () : /*playerObject (NULL), playerPlay (NULL), playerSeek (NULL), playerMuteSolo (NULL), playerVolume (NULL)*/ data (NULL), size (0) {};

        std::string name;
//        SLObjectItf playerObject;
//        SLPlayItf playerPlay;
//        SLSeekItf playerSeek;
//        SLMuteSoloItf playerMuteSolo;
//        SLVolumeItf playerVolume;

        int16_t *data;
        size_t size;

};

/****************************************************************************/

Buffer::Buffer ()
{
        impl = new Impl;
}

/****************************************************************************/

Buffer::~Buffer ()
{
//        // destroy file descriptor audio player object, and invalidate all associated interfaces
//        if (impl->playerObject != NULL) {
//                (*impl->playerObject)->Destroy (impl->playerObject);
//                impl->playerObject = NULL;
//                impl->playerPlay = NULL;
//                impl->playerSeek = NULL;
//                impl->playerMuteSolo = NULL;
//                impl->playerVolume = NULL;
//        }

        // delete impl->data;
        delete impl;
}

/****************************************************************************/

void Buffer::setLoad (std::string const &filename)
{
//        assert (device);
//        SoundContext *ctx = device->getSoundContext ();
//        SLresult result;
//        assert (ctx->app->activity->assetManager);
//        AAsset* asset = AAssetManager_open (ctx->app->activity->assetManager, filename.c_str (), AASSET_MODE_UNKNOWN);
//        assert (asset);
//
//        // open asset as file descriptor
//        off_t start, length;
//        int fd = AAsset_openFileDescriptor(asset, &start, &length);
//        assert(0 <= fd);
//        AAsset_close(asset);
//
//        // configure audio source
//        SLDataLocator_AndroidFD loc_fd = { SL_DATALOCATOR_ANDROIDFD, fd, start, length };
//        SLDataFormat_MIME format_mime = { SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED };
//        SLDataSource audioSrc = { &loc_fd, &format_mime };
//
//        // configure audio sink
//        SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, ctx->outputMixObject };
//        SLDataSink audioSnk = { &loc_outmix, NULL };
//
//        // create audio player
//        const SLInterfaceID ids[3] = { SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME };
//        const SLboolean req[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
//
//        result = (*ctx->engineEngine)->CreateAudioPlayer (ctx->engineEngine, &impl->fdPlayerObject, &audioSrc, &audioSnk, 3, ids, req);
//        assert(SL_RESULT_SUCCESS == result);
//
//        // realize the player
//        result = (*impl->fdPlayerObject)->Realize (impl->fdPlayerObject, SL_BOOLEAN_FALSE);
//        assert(SL_RESULT_SUCCESS == result);
//
//        // get the play interface
//        result = (*impl->fdPlayerObject)->GetInterface (impl->fdPlayerObject, SL_IID_PLAY, &impl->fdPlayerPlay);
//        assert(SL_RESULT_SUCCESS == result);
//
//        // get the seek interface
//        result = (*impl->fdPlayerObject)->GetInterface (impl->fdPlayerObject, SL_IID_SEEK, &impl->fdPlayerSeek);
//        assert(SL_RESULT_SUCCESS == result);
//
//        // get the mute/solo interface
//        result = (*impl->fdPlayerObject)->GetInterface (impl->fdPlayerObject, SL_IID_MUTESOLO, &impl->fdPlayerMuteSolo);
//        assert(SL_RESULT_SUCCESS == result);
//
//        // get the volume interface
//        result = (*impl->fdPlayerObject)->GetInterface (impl->fdPlayerObject, SL_IID_VOLUME, &impl->fdPlayerVolume);
//        assert(SL_RESULT_SUCCESS == result);
//
//        // enable whole file looping
//        result = (*impl->fdPlayerSeek)->SetLoop (impl->fdPlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
//        assert(SL_RESULT_SUCCESS == result);
//
//        // Uruchomienie zapętlonego dźwięku z Asseta
//        // set the player's state
////        result = (*fdPlayerPlay)->SetPlayState (fdPlayerPlay, isPlaying ? SL_PLAYSTATE_PLAYING : SL_PLAYSTATE_PAUSED);
////        result = (*impl->fdPlayerPlay)->SetPlayState (impl->fdPlayerPlay, SL_PLAYSTATE_PLAYING);
////        assert(SL_RESULT_SUCCESS == result);
}

/****************************************************************************/

// this callback handler is called every time a buffer finishes playing
static void playerCallback(SLAndroidSimpleBufferQueueItf bq, void *context)
{
//    assert(bq == bqPlayerBufferQueue);
//    assert(NULL == context);
//    // for streaming playback, replace this test by logic to find and fill the next buffer
//    if (--nextCount > 0 && NULL != nextBuffer && 0 != nextSize) {
//        SLresult result;
//        // enqueue another buffer
//        result = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, nextBuffer, nextSize);
//        // the most likely other result is SL_RESULT_BUFFER_INSUFFICIENT,
//        // which for this code example would indicate a programming error
//        assert(SL_RESULT_SUCCESS == result);
//    }
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

void const *Buffer::getData () const
{
        return impl->data;
}

/****************************************************************************/

size_t Buffer::getSize () const
{
        return impl->size;
}
