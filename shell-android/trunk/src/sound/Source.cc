/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Source.h"
#include <sound/SoundException.h>
#include <util/Exceptions.h>
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "SoundContext.h"
#include "Device.h"
#include "Buffer.h"
#include <stdint.h>

/****************************************************************************/

struct Source::Impl {

        Impl () : playerObject (NULL), playerPlay (NULL), playerSeek (NULL), playerMuteSolo (NULL), playerVolume (NULL), playerBufferQueue (NULL) {};

        SLObjectItf playerObject;
        SLPlayItf playerPlay;
        SLSeekItf playerSeek;
        SLMuteSoloItf playerMuteSolo;
        SLVolumeItf playerVolume;
        SLAndroidSimpleBufferQueueItf playerBufferQueue;
};

/****************************************************************************/

Source::Source () : impl (new Impl)
{
}

/****************************************************************************/

Source::~Source ()
{
        stop ();

        if (impl->playerObject) {
            (*impl->playerObject)->Destroy (impl->playerObject);
        }

        delete impl;
}

/****************************************************************************/

void Source::init ()
{
        assert (device);
        Device *dev = dynamic_cast <Device *> (device);
        assert (dev);
        SoundContext *ctx = dev->getSoundContext ();
        SLresult result;

        // configure audio source
        SLDataLocator_AndroidSimpleBufferQueue loc_bufq = { SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2 };
        SLDataFormat_PCM format_pcm = {
                SL_DATAFORMAT_PCM,                // formatType;
                1,                                // numChannels;
                SL_SAMPLINGRATE_8,                // samplesPerSec;
                SL_PCMSAMPLEFORMAT_FIXED_16,      // bitsPerSample;
                SL_PCMSAMPLEFORMAT_FIXED_16,      // containerSize;
                SL_SPEAKER_FRONT_CENTER,          // channelMask;
                SL_BYTEORDER_LITTLEENDIAN };      // endianness;

        SLDataSource audioSrc = {&loc_bufq, &format_pcm};

        // configure audio sink
        SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, ctx->outputMixObject };
        SLDataSink audioSnk = { &loc_outmix, NULL };

        // create audio player
        const SLInterfaceID ids[3] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND,
                /*SL_IID_MUTESOLO,*/ SL_IID_VOLUME};
        const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,
                /*SL_BOOLEAN_TRUE,*/ SL_BOOLEAN_TRUE};
        result = (*ctx->engineEngine)->CreateAudioPlayer (ctx->engineEngine, &impl->playerObject, &audioSrc, &audioSnk, 3, ids, req);
        assert(SL_RESULT_SUCCESS == result);

        result = (*ctx->engineEngine)->CreateAudioPlayer (ctx->engineEngine, &impl->playerObject, &audioSrc, &audioSnk, 3, ids, req);
        assert(SL_RESULT_SUCCESS == result);

        // realize the player
        result = (*impl->playerObject)->Realize (impl->playerObject, SL_BOOLEAN_FALSE);
        assert(SL_RESULT_SUCCESS == result);

        // get the buffer queue interface
        result = (*impl->playerObject)->GetInterface (impl->playerObject, SL_IID_BUFFERQUEUE, &impl->playerBufferQueue);
        assert(SL_RESULT_SUCCESS == result);

//        // register callback on the buffer queue
//        result = (*impl->playerBufferQueue)->RegisterCallback (impl->playerBufferQueue, bqPlayerCallback, NULL);
//        assert(SL_RESULT_SUCCESS == result);

        // get the play interface
        result = (*impl->playerObject)->GetInterface (impl->playerObject, SL_IID_PLAY, &impl->playerPlay);
        assert(SL_RESULT_SUCCESS == result);

        // get the seek interface
        result = (*impl->playerObject)->GetInterface (impl->playerObject, SL_IID_SEEK, &impl->playerSeek);
        assert(SL_RESULT_SUCCESS == result);

        // get the mute/solo interface
        result = (*impl->playerObject)->GetInterface (impl->playerObject, SL_IID_MUTESOLO, &impl->playerMuteSolo);
        assert(SL_RESULT_SUCCESS == result);

        // get the volume interface
        result = (*impl->playerObject)->GetInterface (impl->playerObject, SL_IID_VOLUME, &impl->playerVolume);
        assert(SL_RESULT_SUCCESS == result);

//        // enable whole file looping
//        result = (*impl->playerSeek)->SetLoop (impl->playerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
//        assert(SL_RESULT_SUCCESS == result);

        // set the player's state
        result = (*impl->playerPlay)->SetPlayState (impl->playerPlay, SL_PLAYSTATE_PLAYING);
        assert(SL_RESULT_SUCCESS == result);
}

/****************************************************************************/

void Source::play (std::string const &bufferName)
{
        assertThrow (device, "Source::play (s) device is NULL");
//        play (device->getBuffer (bufferName));
}

/****************************************************************************/

void Source::play ()
{
        play (buffer);
}

/****************************************************************************/

void Source::play (Sound::IBuffer *buf)
{
        assertThrow (buffer, "Source::play () needs buffer to play. Set it using setBuffer method.");

        SLresult result;
        SLuint32 playerState;

        (*impl->playerObject)->GetState (impl->playerObject, &playerState);
        if (playerState != SL_OBJECT_STATE_REALIZED) {
                throw Sound::SoundException ("PlayerState != SL_OBJECT_STATE_REALIZED");
        }

        int16_t const *lBuffer = static_cast <int16_t const *> (buffer->getData ());
        size_t lLength = buf->getSize ();

        // Removes any sound from the queue.
        result = (*impl->playerBufferQueue)->Clear (impl->playerBufferQueue);
        assert (result == SL_RESULT_SUCCESS);

        // Plays the new sound.
        result = (*impl->playerBufferQueue)->Enqueue (impl->playerBufferQueue, lBuffer, lLength);
        assert (result == SL_RESULT_SUCCESS);
}

/****************************************************************************/

void Source::pause ()
{
}

/****************************************************************************/

void Source::stop ()
{
}

/****************************************************************************/

void Source::rewind ()
{
}

/****************************************************************************/

float Source::getGain () const
{
}

/****************************************************************************/

void Source::setGain (float f)
{
}

/****************************************************************************/

float Source::getPitch () const
{
}

/****************************************************************************/

void Source::setPitch (float f)
{
}

/****************************************************************************/

float Source::getOffset () const
{
        return 0;
}

/****************************************************************************/

void Source::setOffset (float f)
{
}

/****************************************************************************/

Geometry::Point3 Source::getPosition () const
{
        Geometry::Point3 p = {0, 0, 0};
        return p;
}

/****************************************************************************/

void Source::setPosition (Geometry::Point3 &p)
{
}

/****************************************************************************/

Geometry::Point3 Source::getVelocity () const
{
        Geometry::Point3 p = {0, 0, 0};
        return p;
}

/****************************************************************************/

void Source::setVelocity (Geometry::Point3 &p)
{
}

/****************************************************************************/

Geometry::Point3 Source::getDirection () const
{
        Geometry::Point3 p = {0, 0, 0};
        return p;
}

/****************************************************************************/

void Source::setDirection (Geometry::Point3 &p)
{
}

/****************************************************************************/

bool Source::getLooping () const
{
        int i;
        return i;
}

/****************************************************************************/

void Source::setLooping (bool b)
{
}
