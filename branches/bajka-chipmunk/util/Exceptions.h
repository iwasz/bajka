/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EXCEPTIONS_H_
#define BAJKA_EXCEPTIONS_H_

#include <Exception.h>

namespace Util {

struct OperationNotSupportedException : public Core::Exception {

        OperationNotSupportedException (std::string const &s = "") : Core::Exception (s) {}
        virtual ~OperationNotSupportedException () throw () {}

};

struct InitException : public Core::Exception {

        InitException (std::string const &s = "") : Core::Exception (s) {}
        virtual ~InitException () throw () {}

};

struct RuntimeException : public Core::Exception {

        RuntimeException (std::string const &s = "") : Core::Exception (s) {}
        virtual ~RuntimeException () throw () {}

};

} // namespace

#	endif /* EXCEPTIONS_H_ */
