/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include "Listener.h"
#include <sound/SoundException.h>

/****************************************************************************/

float Listener::getGain () const
{
        return 0;
}

/****************************************************************************/

void Listener::setGain (float f)
{
}

/****************************************************************************/

Geometry::Point3 Listener::getPosition () const
{
        Geometry::Point3 p = {0, 0, 0};
        return p;
}

/****************************************************************************/

void Listener::setPosition (Geometry::Point3 &p)
{
}

/****************************************************************************/

Geometry::Point3 Listener::getVelocity () const
{
        Geometry::Point3 p = {0, 0, 0};
        return p;
}

/****************************************************************************/

void Listener::setVelocity (Geometry::Point3 &p)
{
}

/****************************************************************************/

Geometry::Point3 Listener::getAt () const
{
        Geometry::Point3 p = {0, 0, 0};
        return p;
}

/****************************************************************************/

void Listener::setAt (Geometry::Point3 &p)
{
}

/****************************************************************************/

Geometry::Point3 Listener::getUp () const
{
        Geometry::Point3 p = {0, 0, 0};
        return p;
}

/****************************************************************************/

void Listener::setUp (Geometry::Point3 &p)
{
}
