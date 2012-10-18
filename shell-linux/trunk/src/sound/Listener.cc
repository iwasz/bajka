/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Listener.h"
#include <AL/al.h>
#include <AL/alc.h>
#include "SoundException.h"

/****************************************************************************/

float Listener::getGain () const
{
        float f;
        alGetListenerf (AL_GAIN, &f);
        soundThrow ("Listener::getGain : alGetListenerf : ");
        return f;
}

/****************************************************************************/

void Listener::setGain (float f)
{
        alListenerf (AL_GAIN, f);
        soundThrow ("Listener::setGain : alListenerf : ");
}

/****************************************************************************/

Geometry::Point3 Listener::getPosition () const
{
        Geometry::Point3 p = {0, 0, 0};
        alGetListenerfv (AL_POSITION, &p.x);
        soundThrow ("Listener::getPosition : alGetListenerfv : ");
        return p;
}

/****************************************************************************/

void Listener::setPosition (Geometry::Point3 &p)
{
        alListenerfv (AL_POSITION, &p.x);
        soundThrow ("Listener::setPosition : alListenerfv : ");
}

/****************************************************************************/

Geometry::Point3 Listener::getVelocity () const
{
        Geometry::Point3 p = {0, 0, 0};
        alGetListenerfv (AL_VELOCITY, &p.x);
        soundThrow ("Listener::getVelocity : alGetListenerfv : ");
        return p;
}

/****************************************************************************/

void Listener::setVelocity (Geometry::Point3 &p)
{
        alListenerfv (AL_VELOCITY, &p.x);
        soundThrow ("Listener::setVelocity : alListenerfv : ");
}

/****************************************************************************/

Geometry::Point3 Listener::getAt () const
{
        Geometry::Point3 ps[2] = { {0, 0, 0}, {0, 0, 0} };
        alGetListenerfv (AL_ORIENTATION, &ps[0].x);
        soundThrow ("Listener::getAt : alGetListenerfv : ");
        return ps[0];
}

/****************************************************************************/

void Listener::setAt (Geometry::Point3 &p)
{
        ALfloat l[] = {0, 0, 0, 0, 0, 0};
        alGetListenerfv (AL_ORIENTATION, l);
        soundThrow ("Listener::setAt : alGetListenerfv : ");

        l[0] = p.x;
        l[1] = p.y;
        l[2] = p.z;

        alListenerfv (AL_ORIENTATION, l);
        soundThrow ("Listener::setAt : alListenerfv : ");
}

/****************************************************************************/

Geometry::Point3 Listener::getUp () const
{
        Geometry::Point3 ps[2] = { {0, 0, 0}, {0, 0, 0} };
        alGetListenerfv (AL_ORIENTATION, &ps[0].x);
        soundThrow ("Listener::getUp : alGetListenerfv : ");
        return ps[1];
}

/****************************************************************************/

void Listener::setUp (Geometry::Point3 &p)
{
        ALfloat l[] = {0, 0, 0, 0, 0, 0};
        alGetListenerfv (AL_ORIENTATION, l);
        soundThrow ("Listener::setUp : alGetListenerfv : ");

        l[3] = p.x;
        l[4] = p.y;
        l[5] = p.z;

        alListenerfv (AL_ORIENTATION, l);
        soundThrow ("Listener::setUp : alListenerfv : ");
}
