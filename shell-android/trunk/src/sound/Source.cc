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
#include <Platform.h>
#include "Utils.h"

/****************************************************************************/

struct Source::Impl {

        Impl () : playerObject (NULL),
                  playerPlay (NULL),
                  playerSeek (NULL),
                  playerMuteSolo (NULL),
                  playerVolume (NULL),
                  playerBufferQueue (NULL),
                  playbackRate (NULL),
                  maxVolume (0) {};

        SLObjectItf playerObject;
        SLPlayItf playerPlay;
        SLSeekItf playerSeek;
        SLMuteSoloItf playerMuteSolo;
        SLVolumeItf playerVolume;
        SLAndroidSimpleBufferQueueItf playerBufferQueue;
        SLPlaybackRateItf playbackRate;
        SLmillibel maxVolume;
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
                SL_SAMPLINGRATE_44_1,             // samplesPerSec;
                SL_PCMSAMPLEFORMAT_FIXED_16,      // bitsPerSample;
                SL_PCMSAMPLEFORMAT_FIXED_16,      // containerSize;
                SL_SPEAKER_FRONT_CENTER,          // channelMask;
                SL_BYTEORDER_LITTLEENDIAN };      // endianness;

        SLDataSource audioSrc = {&loc_bufq, &format_pcm};

        // configure audio sink
        SLDataLocator_OutputMix loc_outmix = { SL_DATALOCATOR_OUTPUTMIX, ctx->outputMixObject };
        SLDataSink audioSnk = { &loc_outmix, NULL };

        // create audio player
        const SLInterfaceID ids[4] = { SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND, SL_IID_VOLUME, SL_IID_PLAYBACKRATE };
        const SLboolean req[4] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };
        result = (*ctx->engineEngine)->CreateAudioPlayer (ctx->engineEngine, &impl->playerObject, &audioSrc, &audioSnk, 4, ids, req);
        soundThrow (result);

        // realize the player
        result = (*impl->playerObject)->Realize (impl->playerObject, SL_BOOLEAN_FALSE);
        soundThrow (result);

        // get the buffer queue interface
        result = (*impl->playerObject)->GetInterface (impl->playerObject, SL_IID_BUFFERQUEUE, &impl->playerBufferQueue);
        soundThrow (result);

        // get the play interface
        result = (*impl->playerObject)->GetInterface (impl->playerObject, SL_IID_PLAY, &impl->playerPlay);
        soundThrow (result);

        // get the volume interface
        result = (*impl->playerObject)->GetInterface (impl->playerObject, SL_IID_VOLUME, &impl->playerVolume);
        soundThrow (result);

        result = (*impl->playerVolume)->GetVolumeLevel (impl->playerVolume, &impl->maxVolume);
        soundThrow (result);

        // get the play rate interface
        result = (*impl->playerObject)->GetInterface (impl->playerObject, SL_IID_PLAYBACKRATE, &impl->playbackRate);
        soundThrow (result);

        // set the player's state
        result = (*impl->playerPlay)->SetPlayState (impl->playerPlay, SL_PLAYSTATE_PLAYING);
        soundThrow (result);
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

#ifndef NDEBUG
        if (!impl->playerObject) {
                throw Sound::SoundException ("Source::play : source is not initialized. Use init method first.");
        }
#endif

        SLresult result;
        SLuint32 playerState;

#ifndef NDEBUG
        (*impl->playerObject)->GetState (impl->playerObject, &playerState);
        if (playerState != SL_OBJECT_STATE_REALIZED) {
                throw Sound::SoundException ("PlayerState != SL_OBJECT_STATE_REALIZED");
        }
#endif

        int16_t const *lBuffer = static_cast <int16_t const *> (buffer->getData ());
        size_t lLength = buf->getSize ();

        // Removes any sound from the queue.
        result = (*impl->playerBufferQueue)->Clear (impl->playerBufferQueue);
        soundThrow (result);

        result = (*impl->playerPlay)->SetPlayState (impl->playerPlay, SL_PLAYSTATE_PLAYING);
        soundThrow (result);

        // Plays the new sound.
        printlog ("Source::play [%p] len = [%d]", lBuffer, lLength);
        result = (*impl->playerBufferQueue)->Enqueue (impl->playerBufferQueue, lBuffer, lLength);
        soundThrow (result);
}

/****************************************************************************/

void Source::pause ()
{
        SLresult result = (*impl->playerPlay)->SetPlayState (impl->playerPlay, SL_PLAYSTATE_PAUSED);
        soundThrow (result);
}

/****************************************************************************/

void Source::stop ()
{
        SLresult result = (*impl->playerPlay)->SetPlayState (impl->playerPlay, SL_PLAYSTATE_STOPPED);
        soundThrow (result);
}

/****************************************************************************/

void Source::rewind ()
{
        SLuint32 state = 0;
        SLresult result = (*impl->playerPlay)->GetPlayState (impl->playerPlay, &state);
        soundThrow (result);

        result = (*impl->playerPlay)->SetPlayState (impl->playerPlay, SL_PLAYSTATE_STOPPED);
        soundThrow (result);

        if (state == SL_PLAYSTATE_PLAYING) {
                result = (*impl->playerPlay)->SetPlayState (impl->playerPlay, SL_PLAYSTATE_PLAYING);
                soundThrow (result);
        }
}

/****************************************************************************/

float Source::getGain () const
{
        SLmillibel value;
        SLresult result = (*impl->playerVolume)->GetVolumeLevel (impl->playerVolume, &value);
        soundThrow (result);
        return (value - SL_MILLIBEL_MIN) / (impl->maxVolume - SL_MILLIBEL_MIN);
}

/****************************************************************************/

void Source::setGain (float f)
{
        SLmillibel value = f * (impl->maxVolume - SL_MILLIBEL_MIN) + SL_MILLIBEL_MIN;
        SLresult result = (*impl->playerVolume)->SetVolumeLevel (impl->playerVolume, value);
        soundThrow (result);
}

/****************************************************************************/

float Source::getPitch () const
{
        SLpermille value;
        SLresult result = (*impl->playbackRate)->GetRate (impl->playbackRate, &value);
        soundThrow (result);
        return value / 1000.0;
}

/****************************************************************************/

void Source::setPitch (float f)
{
        SLresult result = (*impl->playbackRate)->SetRate (impl->playbackRate, f * 1000.0);
        soundThrow (result);
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
        return false;
}

/****************************************************************************/

void Source::setLooping (bool b)
{
        // TODO
        static bool toBeImplemented = 0;
        assert (toBeImplemented);
}
