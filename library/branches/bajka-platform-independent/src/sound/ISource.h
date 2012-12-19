/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_ITFCES_ISOURCE_H_
#define BAJKA_ITFCES_ISOURCE_H_

#include <util/ReflectionMacros.h>
#include <geometry/Point3.h>

namespace Sound {

class ISource {
public:
        d__
        virtual ~ISource () {}

        virtual void play (std::string const &bufferName) = 0;
        virtual void play () = 0;
        virtual void pause () = 0;
        virtual void stop () = 0;
        virtual void rewind () = 0;

        virtual float getGain () const = 0;
        m_ (setGain) virtual void setGain (float f) = 0;

        virtual float getPitch () const = 0;
        m_ (setPitch) virtual void setPitch (float f) = 0;

        virtual float getOffset () const = 0;
        m_ (setOffset) virtual void setOffset (float f) = 0;

        virtual Geometry::Point3 getPosition () const = 0;
        m_ (setPosition) virtual void setPosition (Geometry::Point3 &p) = 0;

        virtual Geometry::Point3 getVelocity () const = 0;
        m_ (setVelocity) virtual void setVelocity (Geometry::Point3 &p) = 0;

        virtual Geometry::Point3 getDirection () const = 0;
        m_ (setVelocity) virtual void setDirection (Geometry::Point3 &p) = 0;

        virtual bool getLooping () const = 0;
        m_ (setLooping) virtual void setLooping (bool b) = 0;
        E_ (ISource)
};

} /* namespace Sound */
#endif /* ISOURCE_H_ */
