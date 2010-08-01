/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 21, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef IMAPPING_H_
#define IMAPPING_H_

#include <Object.h>

namespace Controller {

/**
 * A Mediator for some objects.
 */
class IMapping : public Core::Object {
public:
        virtual ~IMapping () {}
        virtual void run () = 0;
};

}

#	endif /* IMAPPING_H_ */
