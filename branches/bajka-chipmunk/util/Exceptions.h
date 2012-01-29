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

        const char* what() const throw () { return "OperationNotSupportedException"; }
        std::string getMessage () const { return "OperationNotSupportedException"; }
};

struct InitException : public Core::Exception {

        InitException (std::string const &s = "") : Core::Exception (s) {}
        virtual ~InitException () throw () {}

        const char* what() const throw () { return "InitException"; }
        std::string getMessage () const { return "InitException"; }
};

struct RuntimeException : public Core::Exception {

        RuntimeException (std::string const &s = "") : Core::Exception (s) {}
        virtual ~RuntimeException () throw () {}

        const char* what() const throw () { return "RuntimeException"; }
        std::string getMessage () const { return "RuntimeException"; }
};

} // namespace

#	endif /* EXCEPTIONS_H_ */
