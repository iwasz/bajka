/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  Date : Nov 21, 2009                                                     *
 *  ~~~~~~                                                                  *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#ifndef ISEQUENCE_H_
#define ISEQUENCE_H_

namespace Controller {

template <typename T>
struct ISequence  {
        virtual ~ISequence () {}

        virtual bool hasNext () const = 0;
        virtual const T &next () const = 0;

};

}

#	endif /* ISEQUENCE_H_ */
