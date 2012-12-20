/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_INTERFACE_IBUFFER_H_
#define BAJKA_INTERFACE_IBUFFER_H_

#include <util/ReflectionMacros.h>
#include <string>
#include <core/Object.h>

namespace Sound {

class IBuffer : public Core::Object {
public:
        d__
        virtual ~IBuffer () {}

        m_ (setLoad) virtual void setLoad (std::string const &path) = 0;

        /**
         * Nazwa pod jaką ten bufor będzie dostepny dla źródeł.
         */
        m_ (setName) virtual void setName (std::string const &name) = 0;
        virtual std::string const &getName () const = 0;

        E_ (IBuffer)
};

} /* namespace Sound */
#endif /* IBUFFER_H_ */
