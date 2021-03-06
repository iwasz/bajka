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
#include <sound/pcm/Pcm.h>
#include <util/Exceptions.h>
#include <android/asset_manager.h>
#include <android_native_app_glue.h>
#include <stdint.h>

/****************************************************************************/

struct Buffer::Impl {

        Impl () : data (NULL), size (0) {};

        std::string name;
        void *data;
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
        free (impl->data);
        delete impl;
}

/****************************************************************************/

void Buffer::setLoad (std::string const &filename)
{
        assert (device);
        Sound::load (filename.c_str (), &impl->data, &impl->size);
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
