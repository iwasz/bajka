/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

namespace Util {

struct OperationNotSupportedException : public std::exception {

        virtual ~OperationNotSupportedException () throw () {}
        virtual const char* what() const throw () { return "Bajka not nupported operation"; }

};

} // namespace

#	endif /* EXCEPTIONS_H_ */
