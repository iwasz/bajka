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

namespace Controller {

class IMapping {
public:
        virtual ~IMapping () {}
        virtual void run () = 0;
};

}

#	endif /* IMAPPING_H_ */
