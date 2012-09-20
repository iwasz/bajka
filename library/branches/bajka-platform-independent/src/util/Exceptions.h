/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef BAJKA_EXCEPTIONS_H_
#define BAJKA_EXCEPTIONS_H_

#include <core/Exception.h>

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

struct AssertionException : public Core::Exception {

	AssertionException (std::string const &s = "") : Core::Exception (s) {}
	virtual ~AssertionException () throw () {}
};

} // namespace

#ifdef BAJKA_DEBUG
#define assertThrow(b,msg)                                              \
		if (!(b)) {                                             \
			throw Util::AssertionException ((msg));         \
		}
#else
#define assertThrow(b,msg)
#endif

#	endif /* EXCEPTIONS_H_ */
